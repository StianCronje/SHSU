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
        private float _transactionIncrement;
        private readonly Bank _bank;
        private string _name;
        private Semaphore _mutex;
        private bool _running;
        private int _executionDelay = new Random().Next(1, 3) * 1000;
        private int _delayIncrement = 500;
        private int _minDelay = 500;
        #endregion

        #region public variables
        public float TransactionAmmount
        {
            get => _transactionAmmount;
            set
            {
                if (value.Equals(_transactionAmmount)) return;
                if(_isChild) _transactionAmmount = value >= 0 ? value : 0;
                else _transactionAmmount = value <= 0 ? value : 0;
                _transactionAmmount = value;
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

        public string ActivityString => $"${TransactionAmmount} every {(float) ExecutionDelay / 1000.0f} second" + (ExecutionDelay == 1000 ? "" : "s");

        #endregion

        public Person(string name, float startTransactionAmmount, Bank bank, Semaphore mutex)
        {
            _isChild = startTransactionAmmount < 0;
            Name = name;
            TransactionAmmount = startTransactionAmmount;

            _bank = bank;
            _mutex = mutex;
        }
        
        public async void EarnMoney_Synchronized()
        {
            Running = true;
            while (Running)
            {
                _bank.MakeTransaction(Name, TransactionAmmount, ExecutionMode.Synchronized);

                await Task.Delay(ExecutionDelay);
            }
        }
        
        public async void EarnMoney_Semaphore()
        {
            Running = true;
            while (Running)
            {
                if (_isChild)
                {
                    // Child is spending money

                    if ((_bank.Balance + TransactionAmmount) < 0)
                        return;
                }

                _mutex.WaitOne();
                _bank.MakeTransaction(Name, TransactionAmmount, ExecutionMode.Semaphore);
                _mutex.Release();


                await Task.Delay(ExecutionDelay);
            }
        }

        public Command SpeedUpCommand => new Command(() => ExecutionDelay -= _delayIncrement);
        public Command SlowDownCommand => new Command(() => ExecutionDelay += _delayIncrement);

        public Command HigherTransactionCommand => new Command(() =>
        {
            TransactionAmmount += _isChild ? -_transactionIncrement : _transactionAmmount;
        });
        public Command LowerTransactionCommand => new Command(() =>
        {
            TransactionAmmount -= _isChild ? -_transactionIncrement : _transactionAmmount;
        });

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}