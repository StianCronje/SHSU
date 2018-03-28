using System;
using BankAccount.Models;
using Xamarin.Forms;

namespace BankAccount.Controls
{
    public class TransactionTemplateSelector : DataTemplateSelector
    {
        public DataTemplate DepositTemplate { get; set; }
        public DataTemplate WithdrawalTemplate { get; set; }

        protected override DataTemplate OnSelectTemplate(object item, BindableObject container)
        {
            return ((Transaction)item).Ammount >= 0 ? DepositTemplate : WithdrawalTemplate;
        }
    }
}
