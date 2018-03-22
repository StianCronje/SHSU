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
    public partial class SynchronizedPage : ContentPage
    {
        private SynchronizedViewModel binding;

        public SynchronizedPage()
        {
            InitializeComponent();

            binding = (SynchronizedViewModel)BindingContext;
        }

        private void ListView_OnItemSelected(object sender, SelectedItemChangedEventArgs e)
        {
            ListView.SelectedItem = null;
        }

        private void ListView_OnItemTapped(object sender, ItemTappedEventArgs e)
        {
            ListView.SelectedItem = null;
        }
    }
}