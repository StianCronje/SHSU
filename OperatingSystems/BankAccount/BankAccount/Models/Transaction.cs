using System;
namespace BankAccount.Models
{
    public class Transaction
    {
        public string Name { get; set; }
        public float Ammount{ get; set; }

        public Transaction(string name, float ammount)
        {
            Name = name;
            Ammount = ammount;
        }

        public override string ToString()
        {
            return Name + ": " + Ammount;
        }
    }
}
