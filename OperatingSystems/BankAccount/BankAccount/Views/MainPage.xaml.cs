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

        public MainPage(MainViewModel mainViewModel)
        {
            InitializeComponent();

            mainViewModel.Navigation = Navigation;
            BindingContext = mainViewModel;

            binding = mainViewModel;
        }

		protected override void OnAppearing()
		{
            base.OnAppearing();

            binding.MainViewAppearingCommand.Execute(null);
		}
	}
}