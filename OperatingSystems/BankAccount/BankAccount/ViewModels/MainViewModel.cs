using System.Diagnostics;
using BankAccount.Models;
using BankAccount.Views;
using Xamarin.Forms;

namespace BankAccount.ViewModels
{
    public class MainViewModel
    {
        public INavigation Navigation;

        public Command LoadSemaphoreSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in semaphore mode");
            App.ExecutionMode = ExecutionMode.Semaphore;
            await Navigation.PushAsync(new BankPage(){Title = "Semaphore Solution"});
        });
        public Command LoadSynchronizedSolution => new Command(async () =>
        {
            Debug.WriteLine("load page in synchronized mode");
            App.ExecutionMode = ExecutionMode.Synchronized;
            await Navigation.PushAsync(new BankPage(){Title = "Synchronized Solution"});
        });
    }
}
