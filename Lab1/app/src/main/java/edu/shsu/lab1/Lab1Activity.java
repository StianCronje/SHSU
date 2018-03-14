package edu.shsu.lab1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class Lab1Activity extends AppCompatActivity
{
    TextView helloLabel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lab1);

        Bundle hashmap = this.getIntent().getExtras();
        helloLabel = this.findViewById(R.id.helloLabel);

        if(hashmap != null)
        {
            helloLabel.setText(String.format("%s %s!", getString(R.string.hello), hashmap.get("uname").toString()));
        }
    }
}
