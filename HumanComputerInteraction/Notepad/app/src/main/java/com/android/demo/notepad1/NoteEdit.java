package com.android.demo.notepad1;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class NoteEdit  extends Activity
{
    EditText mTitleText;
    EditText mBodyText;

    String mStartTitle = "";
    String mStartBody = "";

    private NotesDbAdapter mDbHelper;
    private Long mRowId;

    boolean cancelSave = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.note_edit);

        setTitle(R.string.edit_note);

        mDbHelper = new NotesDbAdapter(this);
        mDbHelper.open();

        mTitleText = findViewById(R.id.title);
        mBodyText = findViewById(R.id.body);
        Button confirmButton = findViewById(R.id.confirm);
        Button cancelButton = findViewById(R.id.cancel);

        mRowId = savedInstanceState == null ? null : (Long) savedInstanceState.getSerializable(NotesDbAdapter.KEY_ROWID);
        if(mRowId == null)
        {
            Bundle extras = getIntent().getExtras();
            mRowId = extras != null ? extras.getLong(NotesDbAdapter.KEY_ROWID) : null;
        }


        populateFields();

        mStartTitle = mTitleText.getText().toString();
        mStartBody = mBodyText.getText().toString();

        confirmButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(RESULT_OK);
                finish();
            }
        });
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                cancelChanges();
                setResult(RESULT_OK);
                finish();
            }
        });
        mTitleText.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int i, KeyEvent keyEvent) {
                mBodyText.requestFocus();
                return false;
            }
        });
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        System.out.println("on save state");
        saveState();
        outState.putSerializable(NotesDbAdapter.KEY_ROWID, mRowId);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(cancelSave) return;
        saveState();
    }

    @Override
    protected void onResume() {
        super.onResume();
        saveState();
    }

    private void populateFields()
    {
        if(mRowId != null)
        {
            Cursor note = mDbHelper.fetchNote(mRowId);
            startManagingCursor(note);
            mTitleText.setText(note.getString(note.getColumnIndexOrThrow(NotesDbAdapter.KEY_TITLE)));
            mBodyText.setText(note.getString(note.getColumnIndexOrThrow(NotesDbAdapter.KEY_BODY)));
        }
    }

    private void saveState()
    {
        String title = mTitleText.getText().toString();
        String body = mBodyText.getText().toString();

        if(mRowId == null)
        {
            long id = mDbHelper.createNote(title, body);
            if(id > 0)
                mRowId = id;
        }
        else
        {
            mDbHelper.updateNote(mRowId, title, body);
        }
    }

    private void cancelChanges()
    {
        cancelSave = true;
        if(mRowId != null)
        {
            if(mStartTitle.isEmpty() && mStartBody.isEmpty())
                mDbHelper.deleteNote(mRowId);
            else
                mDbHelper.updateNote(mRowId, mStartTitle, mStartBody);
        }
    }
}
