using Xamarin.Forms;
using System.Collections.ObjectModel;
using BankAccount.ViewModels;
using System.Diagnostics;

namespace BankAccount
{
    public partial class BankAccountPage : ContentPage
    {        
        BankViewModel binding;

        public BankAccountPage()
        {
            InitializeComponent();

            binding = (BankViewModel)BindingContext;


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
