using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using BankAccount.Models;
using Xamarin.Forms;

namespace BankAccount.ViewModels
{
    public class SynchronizedViewModel
    {
        public Action<ObservableCollection<Transaction>> OnMessageInsertAction;

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

        public Command PageLoadCqommand => new Command(() =>
        {
            Debug.WriteLine("Page Loaded");
        });

        public Command SubmitCommand => new Command(() => {
            Debug.WriteLine("Submit: " + MessageText);
        });

        public Command<Transaction> DeleteMessageCommand => new Command<Transaction>(message =>
        {
            Debug.WriteLine("delete: ");
        });


        public event PropertyChangedEventHandler PropertyChanged;
        //[NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
