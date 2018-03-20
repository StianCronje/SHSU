namespace BankAccount.UWP
{
    public sealed partial class MainPage
    {
        public MainPage()
        {
            this.InitializeComponent();

            LoadApplication(new BankAccount.App());
        }
    }
}
