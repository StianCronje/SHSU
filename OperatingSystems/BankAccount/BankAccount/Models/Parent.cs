using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Threading;
using BankAccount.Annotations;

namespace BankAccount.Models
{
    public class Parent : INotifyPropertyChanged
    {
        private float _earningAmmount;
        private readonly Bank _bank;

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

        public void EarnMoney()
        {
            if (_bank.Semaphore == null)
            {
                EarnMoney_Synchronized();
            }
            else
            {
                EarnMoney_Semaphore();
            }
        }

        private void EarnMoney_Synchronized()
        {
            _bank.MakeTransaction(EarningAmmount);
        }

        private void EarnMoney_Semaphore()
        {
            _bank.Semaphore.WaitOne();
            _bank.MakeTransaction(EarningAmmount);
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