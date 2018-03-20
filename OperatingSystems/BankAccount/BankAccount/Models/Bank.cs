using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Threading;
using BankAccount.Annotations;

namespace BankAccount.Models
{
    public class Bank : INotifyPropertyChanged
    {
        readonly object mutex = new object();
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
        
        public Semaphore Semaphore { get; set; }

        public Bank()
        {
            Balance = 0;
        }

        public void MakeTransaction(float ammount)
        {
            if (Semaphore == null)
            {
                MakeTransaction_Synchronized(ammount);
            }
            else
            {
                MakeTransaction_Semaphore(ammount);
            }
        }

        private void MakeTransaction_Synchronized(float ammount)
        {
            lock (mutex)
            {
                Balance += ammount;
            }
        }

        private void MakeTransaction_Semaphore(float ammount)
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