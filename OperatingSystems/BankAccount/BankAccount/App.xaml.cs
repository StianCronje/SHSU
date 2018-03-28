using BankAccount.Models;
using BankAccount.ViewModels;
using BankAccount.Views;
using Xamarin.Forms;

namespace BankAccount
{
    public partial class App : Application
    {
        public static NavigationPage MainNav;
        public App()
        {
            InitializeComponent();

            MainNav = new NavigationPage(new MainPage(new MainViewModel()));

            MainPage = MainNav;
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
