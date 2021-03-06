﻿using System.Diagnostics;
using BankAccount.Models;
using BankAccount.Views;
using Xamarin.Forms;

namespace BankAccount.ViewModels
{
    public class MainViewModel
    {
        public INavigation Navigation;

        public Command MainViewAppearingCommand => new Command(() =>
        {
            App.MainNav.BarBackgroundColor = Color.White;
        });

        public Command LoadSemaphoreSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in semaphore mode");
            App.ExecutionMode = ExecutionMode.Semaphore;
            await Navigation.PushAsync(new BankPage() { Title = "Semaphore Solution" });
            App.MainNav.BarBackgroundColor = Color.FromHex("#039be5");
        });
        public Command LoadSynchronizedSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in synchronized mode");
            App.ExecutionMode = ExecutionMode.Synchronized;
            await Navigation.PushAsync(new BankPage() { Title = "Synchronized Solution" });
            App.MainNav.BarBackgroundColor = Color.FromHex("#ff7043");
        });
    }
}
