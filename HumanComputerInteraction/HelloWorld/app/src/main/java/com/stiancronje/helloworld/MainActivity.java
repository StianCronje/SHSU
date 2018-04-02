package com.stiancronje.helloworld;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TextView textView;
    EditText editText;
    Button button;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.textView1);
        editText = findViewById(R.id.editText1);
        button = findViewById(R.id.button1);

        button.setOnClickListener(new ButtonListener());
    }

    private class ButtonListener implements View.OnClickListener
    {
        public void onClick(View V)
        {
            String name = editText.getText().toString();

            if(!name.equals(""))
            {
                textView.setText(String.format("%s %s!", getString(R.string.hello) ,name));
            }
            else
            {
                textView.setText(getString(R.string.enter_name));
            }
        }
    }

}
