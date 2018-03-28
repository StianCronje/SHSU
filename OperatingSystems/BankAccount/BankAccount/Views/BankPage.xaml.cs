using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BankAccount.ViewModels;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace BankAccount.Views
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class BankPage : ContentPage
    {
        public BankPage()
        {
            InitializeComponent();

            TransactionListView.ItemSelected += (sender, e) => { ((ListView) sender).SelectedItem = null; };
            TransactionListView.ItemTapped += (sender, args) => { ((ListView) sender).SelectedItem = null; };
        }
    }
}