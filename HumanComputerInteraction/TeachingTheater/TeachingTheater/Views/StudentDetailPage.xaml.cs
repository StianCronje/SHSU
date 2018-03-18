using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using TeachingTheater.Models;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace TeachingTheater.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class StudentDetailPage : ContentPage
    {
        public StudentDetailPage(Computer computer)
        {
            InitializeComponent();

            BindingContext = computer;
        }

        public StudentDetailPage()
        {
            InitializeComponent();
        }
    }
}