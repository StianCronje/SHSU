using BankAccount.Models;
using BankAccount.ViewModels;
using BankAccount.Views;
using Xamarin.Forms;

namespace BankAccount
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();

            MainPage = new NavigationPage(new MainPage(new MainViewModel()));
        }

        protected override void OnStart()
        {
            // Handle when your app starts
        }

        protected override void OnSleep()
        {
            // Handle when your app sleeps
        }

        protected override void OnResume()
        {
            // Handle when your app resumes
        }

        public static ExecutionMode ExecutionMode { get; set; }
    }
}
