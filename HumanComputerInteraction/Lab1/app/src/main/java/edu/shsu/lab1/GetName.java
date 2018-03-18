package edu.shsu.lab1;


import android.content.Intent;
import android.os.Bundle;
import android.app.Activity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

/**
 * Created by Stian on 3/14/2018.
 */

public class GetName extends Activity implements View.OnClickListener
{
    EditText name;
    Button button;

    @Override
    public void onClick(View view)
    {
        /*
        Retrieve the user entered text from the text field and keep it in a local String variable.
        Create an android.content.Intent object: new Intent(this, Lab1Activity.class).
         */

        Intent intent = new Intent(this, Lab1Activity.class);
        intent.putExtra("uname", name.getText().toString());
        this.startActivity(intent);
    }

    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.name_getter);

        name = this.findViewById(R.id.nameField);
        button = this.findViewById(R.id.submitButton);

        button.setOnClickListener(this);
    }
}
