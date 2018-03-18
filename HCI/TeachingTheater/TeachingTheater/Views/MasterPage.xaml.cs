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
	public partial class MasterPage : MasterDetailPage
	{
        public static MasterPage Instance;

		public MasterPage ()
		{
			InitializeComponent ();
            Instance = this;

            SetDetailPage(new TeacherDetailPage());
        }

        public void SetDetailPage(Page page)
        {
            Detail = new NavigationPage(page);
            IsPresented = false;
        }
	}
}