using Android.App;
using Android.Widget;
using Android.OS;

namespace HelloAndroid.Droid
{
    [Activity(Label = "HelloAndroid", MainLauncher = true, Icon = "@mipmap/icon")]
    public class MainActivity : Activity
    {
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            // Get our button from the layout resource,
            // and attach an event to it
            Button button = FindViewById<Button>(Resource.Id.myButton);
            EditText editText = FindViewById<EditText>(Resource.Id.editText1);
            TextView textView = FindViewById<TextView>(Resource.Id.helloText);

            button.Click += delegate {

                string name = editText.Text;

                textView.Text = "Hello " + (string.IsNullOrWhiteSpace(name) ? "Android" : name) + "!";

            };
        }
    }
}

