using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Threading;
using BankAccount.Annotations;
using Xamarin.Forms;

namespace BankAccount.Models
{
    public class Bank : INotifyPropertyChanged
    {
        readonly object mutex = new object();
        private float _balance;
        private ObservableCollection<Transaction> _transactions = new ObservableCollection<Transaction>(){
            new Transaction("name", 12),
            new Transaction("name", -2),
            new Transaction("name", 5),
            new Transaction("name", -10),
            new Transaction("name", 4)
        };


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

        public ObservableCollection<Transaction> Transactions
        {
            get => _transactions;
            set
            {
                if (Equals(value, _transactions)) return;
                _transactions = value;
                OnPropertyChanged();
            }
        }
        
        public Bank()
        {
            Balance = 0;
        }

        public void MakeTransaction(string name, float ammount)
        {

            if (App.ExecutionMode == ExecutionMode.Synchronized)
            {
                MakeTransaction_Synchronized(ammount);
            }
            else
            {
                MakeTransaction_Semaphore(ammount);
            }
            Device.BeginInvokeOnMainThread(() =>
            {
                Transactions.Insert(0, new Transaction(name, ammount));
            });
            
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