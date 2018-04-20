package com.stiancronje.androideventhandling;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity {

    TextView textView;
    Button button;
    ToggleButton toggleButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.text);
        button = findViewById(R.id.btn);
        toggleButton = findViewById(R.id.toggle);

//        ClickListener listener =



        toggleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String t;
                Context context = getApplicationContext();

                t = toggleButton.isChecked() ? "Ringer On" : "Ringer Off";

                Toast.makeText(context, t, Toast.LENGTH_SHORT).show();
            }
        });


    }

    public void ButtonHandler(View v)
    {
        Toast.makeText(getApplicationContext(), "Button clicked", Toast.LENGTH_SHORT).show();
    }

    class ClickListener implements View.OnClickListener
    {

        @Override
        public void onClick(View view) {

        }
    }
}
