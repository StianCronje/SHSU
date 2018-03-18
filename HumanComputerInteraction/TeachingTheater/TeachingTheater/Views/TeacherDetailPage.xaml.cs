using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace TeachingTheater.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class TeacherDetailPage : ContentPage
	{
        float StepValue = 1f;

        public TeacherDetailPage ()
		{
			InitializeComponent ();

            LightSlider.Value = 5;
		}

        private void Slider_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            var newStep = Math.Round(e.NewValue / StepValue);

            LightSlider.Value = newStep * StepValue;
        }
    }
}