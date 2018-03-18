using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Threading.Tasks;

using TeachingTheater.Models;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace TeachingTheater.Views
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class ComputersPage : ContentPage
    {
        ObservableCollection<Computer> StudentComputers;

        public ComputersPage()
        {
            InitializeComponent();
            //Items = new ObservableCollection<string>
            //{
            //    "HCI_Student_001",
            //    "HCI_Student_002",
            //    "HCI_Student_003",
            //    "HCI_Student_004",
            //    "HCI_Student_005",
            //    "HCI_Student_006",
            //    "HCI_Student_007",
            //    "HCI_Student_008"
            //};

            StudentComputers = new ObservableCollection<Computer>
            {
                new Computer{Name = "Teacher Controls", Description="Teacher", DetailPage=typeof(TeacherDetailPage)},
                new Computer{Name = "HCI_Student_001", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_002", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_003", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_004", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_005", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_006", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_007", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_008", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_009", Description="Student", DetailPage=typeof(StudentDetailPage)},
                new Computer{Name = "HCI_Student_010", Description="Student", DetailPage=typeof(StudentDetailPage)}
            };

            MyListView.ItemsSource = StudentComputers;
            //MyListView.BackgroundColor = Color.FromHex("#96d1ff");
        }

        void Handle_ItemTapped(object sender, ItemTappedEventArgs e)
        {
            if (e.Item == null)
                return;

            Computer tapped = e.Item as Computer;
            Page load = (Page)Activator.CreateInstance(tapped.DetailPage);
            load.Title = tapped.Name;
            MasterPage.Instance.SetDetailPage(load);

            //Deselect Item
            ((ListView)sender).SelectedItem = null;

        }
    }
}
