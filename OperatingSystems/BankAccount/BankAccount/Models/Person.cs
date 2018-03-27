using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;
using BankAccount.Annotations;
using Xamarin.Forms;

namespace BankAccount.Models
{
    public class Person : INotifyPropertyChanged
    {
        #region private variables
        private bool _isChild;
        private float _transactionAmmount;
        private int _transactionIncrementMin = 1;
        private int _transactionIncrementMax = 20;
        private readonly Bank _bank;
        private string _name;
        private Semaphore _mutex;
        private bool _running;
        private int _executionDelay;
        private int _delayIncrement = 500;
        private int _minDelay = 500;

        private Random _random;
        #endregion

        #region public variables
        public float TransactionAmmount
        {
            get => _transactionAmmount;
            set
            {
                if (value.Equals(_transactionAmmount)) return;
                if(_isChild){
                    _transactionAmmount = value <= 0 ? value : 0;
                } 
                else{
                _transactionAmmount = value >= 0 ? value : 0;
                } 
                //_transactionAmmount = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(ActivityString));
            }
        }

        public string Name
        {
            get => _name;
            set
            {
                if (value == _name) return;
                _name = value;
                OnPropertyChanged();
            }
        }

        public bool Running
        {
            get => _running;
            set
            {
                if (value == _running) return;
                _running = value;
                OnPropertyChanged();
            }
        }

        public int ExecutionDelay
        {
            get => _executionDelay;
            set
            {
                if (value == _executionDelay) return;
                _executionDelay = value >= _minDelay ? value : _minDelay;
                OnPropertyChanged();
                OnPropertyChanged(nameof(ActivityString));
            }
        }

        public string ActivityString => $"${Math.Abs(TransactionAmmount)} every {(float) ExecutionDelay / 1000.0f} second" + (ExecutionDelay == 1000 ? "" : "s");

        #endregion

        /// <summary>
        /// Initializes a new instance of the <see cref="T:BankAccount.Models.Person"/> class.
        /// </summary>
        /// <param name="name">Name of the person.</param>
        /// <param name="startTransactionAmmount">Start transaction ammount.</param>
        /// <param name="bank">Reference to shared bank account Bank.</param>
        /// <param name="mutex">Mutex. (Will only be used if App.ExecutionMode is in semaphore mode)</param>
        public Person(string name, float startTransactionAmmount, Bank bank, Semaphore mutex)
        {
            _isChild = (startTransactionAmmount < 0);
            Name = name;
            TransactionAmmount = startTransactionAmmount;

            _bank = bank;
            _mutex = mutex;
            _random = new Random(DateTime.Now.Second);
            _executionDelay = _random.Next(1, 3) * 1000;
        }

        /// <summary>
        /// Make a transaction on the Bank account.
        /// Will be synchronized or use semaphores based on App.ExecutionMode
        /// </summary>
        public async void ProcessMoney()
        {
            switch (App.ExecutionMode)
            {
                case ExecutionMode.Semaphore:
                    await ProcessMoney_Semaphore();
                    break;
                case ExecutionMode.Synchronized:
                    await ProcessMoney_Synchronized();
                    break;
                default:
                    break;
            }
        }
        
        async Task ProcessMoney_Synchronized()
        {
            Running = true;
            while (Running)
            {
                _bank.MakeTransaction(Name, TransactionAmmount);

                await Task.Delay(ExecutionDelay);
            }
        }
        
        async Task ProcessMoney_Semaphore()
        {
            Running = true;
            while (Running)
            {
                _mutex.WaitOne();
                _bank.MakeTransaction(Name, TransactionAmmount);
                _mutex.Release();
                await Task.Delay(ExecutionDelay);
            }
        }

        /// <summary>
        /// Speed up transaction rate basd on preset increment.
        /// </summary>
        public Command SpeedUpCommand => new Command(() => ExecutionDelay -= _delayIncrement);

        /// <summary>
        /// Slow down transaction rate basd on preset increment.
        /// </summary>
        public Command SlowDownCommand => new Command(() => ExecutionDelay += _delayIncrement);

        /// <summary>
        /// Spend more if this is a child
        /// Earn more if this is a parent
        /// </summary>
        public Command HigherTransactionCommand => new Command(() =>
        {
            TransactionAmmount += _isChild ? -GetRandomIncrement() : GetRandomIncrement();
        });

        /// <summary>
        /// Spend less if this is a child
        /// Earn less if this is a parent
        /// </summary>
        public Command LowerTransactionCommand => new Command(() =>
        {
            TransactionAmmount -= _isChild ? -GetRandomIncrement() : GetRandomIncrement();
        });


        int GetRandomIncrement()
        {
            return _random.Next(_transactionIncrementMin, _transactionIncrementMax);
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}