using System.ComponentModel;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Threading;
using BankAccount.Annotations;

namespace BankAccount.Models
{
    public class Child : INotifyPropertyChanged
    {
        private float _spendAmmount;
        private Bank _bank;
        private Semaphore _semaphore;

        public float SpendAmmount
        {
            get => _spendAmmount;
            set
            {
                if (value.Equals(_spendAmmount)) return;
                _spendAmmount = value;
                OnPropertyChanged();
            }
        }

        public Child(float startSpendAmmount, Bank bank)
        {
            SpendAmmount = startSpendAmmount;
            _bank = bank;
        }
        public Child(float startSpendAmmount, Bank bank, Semaphore sema)
        {
            SpendAmmount = startSpendAmmount;
            _bank = bank;
            _semaphore = sema;
        }

        public void SpendMoney()
        {
            if (_semaphore == null)
            {
                SpendMoney_Synchronized();
            }
            else
            {
                SpendMoney_Semaphore();
            }
        }

        void SpendMoney_Synchronized()
        {
            _bank.MakeTransaction_Synchronized(-SpendAmmount);
        }
        void SpendMoney_Semaphore()
        {
            _semaphore.WaitOne();
            _bank.MakeTransaction_Semaphore(-SpendAmmount);
            _semaphore.Release();
        }


        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}