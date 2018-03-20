using System.ComponentModel;
using System.Runtime.CompilerServices;
using BankAccount.Annotations;

namespace BankAccount.Models
{
    public class Bank : INotifyPropertyChanged
    {
        object mutex = new object();
        private float _balance;


        public float Balance
        {
            get => _balance;
            set
            {
                if (value.Equals(_balance)) return;
                _balance = value;
                OnPropertyChanged();
            }
        }
        
        //TODO make a semaphore

        public Bank()
        {
            Balance = 0;
        }

        public void MakeTransaction_Synchronized(float ammount)
        {
            lock (mutex)
            {
                Balance += ammount;
            }
        }

        public void MakeTransaction_Semaphore(float ammount)
        {
            Balance += ammount;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}