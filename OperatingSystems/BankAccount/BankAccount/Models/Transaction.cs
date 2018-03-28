using System;
namespace BankAccount.Models
{
    public class Transaction
    {
        public string Name { get; set; }
        public float Ammount{ get; set; }
        public float AvailableBalance { get; set; }

        public Transaction(string name, float ammount, float balance)
        {
            Name = name;
            Ammount = ammount;
            AvailableBalance = balance;
        }

        public override string ToString()
        {
            return Name + ": " + Ammount;
        }
    }
}
