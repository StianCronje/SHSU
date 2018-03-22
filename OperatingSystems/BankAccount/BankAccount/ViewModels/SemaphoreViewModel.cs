using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Tasks;
using BankAccount.Models;
using Xamarin.Forms;

namespace BankAccount.ViewModels
{

    //TODO use execution mode enum to chage the way everything executes
    public class SemaphoreViewModel : INotifyPropertyChanged
    {
        #region Actions

        public Action<ObservableCollection<Transaction>> OnMessageInsertAction;

        #endregion

        #region private variable

        private string _messageText;
        private Bank _bank = new Bank();
        private Task _parentTask1;
        private Task _parentTask2;
        private Person _parent1;
        private Person _parent2;
        private ObservableCollection<Person> _children = new ObservableCollection<Person>();
        private List<Task> _childrenTasks = new List<Task>(0);

        #endregion

        #region public variables

        public Semaphore mutexSemaphore = new Semaphore(1, 1);
        public Semaphore emptySemaphore = new Semaphore(1, 1);

        public Bank Bank
        {
            get => _bank;
            set
            {
                if (Equals(value, _bank)) return;
                _bank = value;
                OnPropertyChanged();
            }
        }

        public Person Parent1
        {
            get => _parent1;
            set
            {
                if (value == _parent1) return;
                _parent1 = value;
                OnPropertyChanged();
            }
        }
        public Person Parent2
        {
            get => _parent2;
            set
            {
                if (value == _parent2) return;
                _parent2 = value;
                OnPropertyChanged();
            }
        }


        public ObservableCollection<Person> Children
        {
            get => _children;
            set
            {
                if (value == _children) return;
                _children = value;
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

        #endregion


        public SemaphoreViewModel()
        {
            Parent1 = new Person("Parent 1", 10, Bank, mutexSemaphore);
            _parentTask1 = new Task(Parent1.ProcessMoney);
            Parent2 = new Person("Parent 2", 10, Bank, mutexSemaphore);
            _parentTask2 = new Task(Parent2.ProcessMoney);

            _parentTask1.Start();
            _parentTask2.Start();
        }

        public Command AddChildCommand => new Command(() =>
        {
            Person child = new Person("Child " + (Children.Count + 1), -2, Bank, mutexSemaphore);
            Children.Add(child);
            _childrenTasks.Add(new Task(child.ProcessMoney));
            _childrenTasks[_childrenTasks.Count-1].Start();
        });

        public Command<Person> DeleteChildCommand => new Command<Person>(child =>
        {
            var index = Children.IndexOf(child);
            if(index < 0) return;
            Children[index].Running = false;
            _childrenTasks.RemoveAt(index);
            Children.RemoveAt(index);
        });


        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
