using SymptomAssessment.Controls;
using SymptomAssessment.UWP.Controls;
using Xamarin.Forms;
using Xamarin.Forms.Platform.UWP;

[assembly: ExportRenderer(typeof(CustomSwitch), typeof(CustomSwitchRendererUWP))]
namespace SymptomAssessment.UWP.Controls
{
    public class CustomSwitchRendererUWP : SwitchRenderer
    {
        protected override void OnElementChanged(ElementChangedEventArgs<Switch> e)
        {
            base.OnElementChanged(e);

            if (e.OldElement == null)
            {
                var customSwitch = e.NewElement as CustomSwitch;
                
                Control.OnContent = customSwitch.OnText;
                Control.OffContent = customSwitch.OffText;
            }
        }
    }
}