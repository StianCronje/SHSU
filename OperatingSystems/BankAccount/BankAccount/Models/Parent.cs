using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Threading;
using BankAccount.Annotations;

namespace BankAccount.Models
{
    public class Parent : INotifyPropertyChanged
    {
        private float _earningAmmount;
        private Bank _bank;
        private Semaphore _semaphore = null;

        public float EarningAmmount
        {
            get => _earningAmmount;
            set
            {
                if (value.Equals(_earningAmmount)) return;
                _earningAmmount = value;
                OnPropertyChanged();
            }
        }

        public Parent(float startEarningAmmount, Bank bank)
        {
            EarningAmmount = startEarningAmmount;
            _bank = bank;
        }

        public Parent(float startEarningAmmount, Bank bank, Semaphore sema)
        {
            EarningAmmount = startEarningAmmount;
            _bank = bank;
            _semaphore = sema;
        }

        public void EarnMoney()
        {
            if (_semaphore == null)
            {
                EarnMoney_Synchronized();
            }
            else
            {
                EarnMoney_Semaphore();
            }
        }

        void EarnMoney_Synchronized()
        {
            _bank.MakeTransaction_Synchronized(EarningAmmount);
        }
        void EarnMoney_Semaphore()
        {
            _semaphore.WaitOne();
            _bank.MakeTransaction_Semaphore(EarningAmmount);
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