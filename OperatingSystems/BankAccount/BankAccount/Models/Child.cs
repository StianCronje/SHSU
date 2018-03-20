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

        public void SpendMoney()
        {
            if (_bank.Semaphore == null)
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
            _bank.MakeTransaction(-SpendAmmount);
        }
        void SpendMoney_Semaphore()
        {
            _bank.Semaphore.WaitOne();
            _bank.MakeTransaction(-SpendAmmount);
            _bank.Semaphore.Release();
        }


        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}