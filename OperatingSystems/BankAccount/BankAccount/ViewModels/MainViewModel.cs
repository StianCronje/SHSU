using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using BankAccount.Models;
using BankAccount.Views;
using Xamarin.Forms;

namespace BankAccount.ViewModels
{
    public class MainViewModel
    {
        public Action<ObservableCollection<Transaction>> OnMessageInsertAction;

        public INavigation Navigation;

        private string _messageText;
        private ObservableCollection<Transaction> _messages = new ObservableCollection<Transaction>(){
            new Transaction("name", 12),
            new Transaction("name", -2),
            new Transaction("name", 5),
            new Transaction("name", -10),
            new Transaction("name", 4)
        };


        public ObservableCollection<Transaction> Messages
        {
            get => _messages;
            set
            {
                if (Equals(value, _messages)) return;
                _messages = value;
                OnPropertyChanged();
            }
        }

        public string MessageText
        {
            get => _messageText;
            set
            {
                if (value == _messageText) return;
                _messageText = value;
                OnPropertyChanged();
            }
        }

        public Command SpendRandom => new Command(() =>
        {
            AddTransaction("Child", new Random().Next(-100, 100));
        });

        public void AddTransaction(string name, float ammount)
        {
            Messages.Insert(0, new Transaction(name, ammount));
        }

        public Command LoadSemaphoreSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in semaphore mode");
            App.ExecutionMode = ExecutionMode.Semaphore;
            await Navigation.PushAsync(new SemaphorePage());
        });
        public Command LoadSynchronizedSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in synchronized mode");
            App.ExecutionMode = ExecutionMode.Synchronized;
            await Navigation.PushAsync(new SynchronizedPage());
        });


        public event PropertyChangedEventHandler PropertyChanged;
        //[NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
