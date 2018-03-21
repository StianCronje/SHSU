using Xamarin.Forms;

namespace SymptomAssessment.Controls
{
    public class CustomSwitch : Switch
    {
        public static readonly BindableProperty OnTextProperty = BindableProperty.Create(
            propertyName: "OnText",
            returnType: typeof(string),
            declaringType: typeof(CustomSwitch),
            defaultValue: "On",
            defaultBindingMode: BindingMode.TwoWay,
            propertyChanged: OnTextPropertyChanged);

        private static void OnTextPropertyChanged(BindableObject bindable, object oldValue, object newValue)
        {
            var control = (CustomSwitch)bindable;
            control.OnText = newValue.ToString();
        }

        public static readonly BindableProperty OffTextProperty = BindableProperty.Create(
            propertyName: "OffText",
            returnType: typeof(string),
            declaringType: typeof(CustomSwitch),
            defaultValue: "Off",
            defaultBindingMode: BindingMode.TwoWay,
            propertyChanged: OffTextPropertyChanged);

        private static void OffTextPropertyChanged(BindableObject bindable, object oldValue, object newValue)
        {
            var control = (CustomSwitch)bindable;
            control.OffText = newValue.ToString();
        }

        public string OnText
        {
            get { return (string)GetValue(OnTextProperty).ToString(); }
            set { SetValue(OnTextProperty, value); }
        }
        public string OffText
        {
            get { return (string)GetValue(OffTextProperty).ToString(); }
            set { SetValue(OffTextProperty, value); }
        }
    }
}