using System;
namespace BankAccount.Models
{
    public class Transaction
    {


        public string ID { get; set; }
        public string Name { get; set; }
        public string MessageContent { get; set; }

        public Transaction(string name, string messageContent)
        {
            Name = name;
            MessageContent = messageContent;
        }

        public override string ToString()
        {
            return ID + " _ " + Name + ": " + MessageContent;
        }
    }
}
