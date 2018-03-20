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
    public partial class MainPage : ContentPage
    {
        private MainViewModel binding;

        public MainPage()
        {
            InitializeComponent();

            binding = (MainViewModel)BindingContext;
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();

            binding.OnMessageInsertAction += (messages) =>
            {
                var index = messages.Count - 1;
                Device.BeginInvokeOnMainThread(() =>
                {

                    ListView.ScrollTo(messages[index], ScrollToPosition.End, true);
                });
            };

            binding.PageLoadCqommand.Execute(null);
            Debug.WriteLine("test");
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