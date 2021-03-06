﻿using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;
using BankAccount.Annotations;
using Xamarin.Forms;

namespace BankAccount.Models
{
    public class Bank : INotifyPropertyChanged
    {
        readonly object mutex = new object();
        private float _balance;
        private ObservableCollection<Transaction> _transactions = new ObservableCollection<Transaction>();


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

        //public void MakeTransaction(string name, float ammount)
        //{

        //    if (App.ExecutionMode == ExecutionMode.Synchronized)
        //    {
        //        MakeTransaction_Synchronized(ammount);
        //    }
        //    else
        //    {
        //        MakeTransaction_Semaphore(ammount);
        //    }
        //    Device.BeginInvokeOnMainThread(() =>
        //    {
        //        Transactions.Insert(0, new Transaction(name, ammount, Balance));
        //    });
            
        //}

        public void MakeTransaction_Synchronized(string name, float ammount)
        {
            lock (mutex)
            {
                if ((Balance + ammount) >= 0)
                {
                    Balance += ammount;

                    float tempBalance = Balance;

                    Device.BeginInvokeOnMainThread(() =>
                    {
                        Transactions.Insert(0, new Transaction(name, ammount, tempBalance));
                    });
                }
            }
        }

        public void MakeTransaction_Semaphore(string name, float ammount)
        {

            if ((Balance + ammount) >= 0)
            {
                Balance += ammount;

                float tempBalance = Balance;

                Device.BeginInvokeOnMainThread(() =>
                {
                    Transactions.Insert(0, new Transaction(name, ammount, tempBalance));
                });
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}