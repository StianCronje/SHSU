/*
 * Copyright (C) 2008 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.demo.notepad1;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;


public class Notepadv1 extends ListActivity
{
    private static final int ACTIVITY_CREATE=0;
    private static final int ACTIVITY_EDIT=1;

    private static final int INSERT_ID = Menu.FIRST;
    private static final int DELETE_ID = Menu.FIRST + 1;

    private NotesDbAdapter mDbHelper;

    TextView emptyText;


    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.notepad_list);
        emptyText = findViewById(R.id.empty);

        mDbHelper = new NotesDbAdapter(this);
        mDbHelper.open();
        fillData();

        registerForContextMenu(getListView());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        boolean result = super.onCreateOptionsMenu(menu);
        menu.add(0, INSERT_ID, 0, R.string.menu_insert);
        return result;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case INSERT_ID:
                createNote();
                return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo)
    {
        super.onCreateContextMenu(menu, v, menuInfo);
        menu.add(0, DELETE_ID, 0, R.string.menu_delete);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case DELETE_ID:
                AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
                mDbHelper.deleteNote(info.id);
                fillData();
                return true;
        }

        return super.onContextItemSelected(item);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id)
    {
        super.onListItemClick(l, v, position, id);

//        Cursor cursor = mNotesCursor;
//        cursor.moveToPosition(position);
        Intent intent = new Intent(this, NoteEdit.class);
        intent.putExtra(NotesDbAdapter.KEY_ROWID, id);
//        intent.putExtra(NotesDbAdapter.KEY_TITLE, cursor.getString(cursor.getColumnIndexOrThrow(NotesDbAdapter.KEY_TITLE)));
//        intent.putExtra(NotesDbAdapter.KEY_BODY, cursor.getString(cursor.getColumnIndexOrThrow(NotesDbAdapter.KEY_BODY)));
        startActivityForResult(intent, ACTIVITY_EDIT);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent intent)
    {
        super.onActivityResult(requestCode, resultCode, intent);

        fillData();

    }

    private void fillData()
    {
        Cursor cursor = mDbHelper.fetchAllNotes();
        startManagingCursor(cursor);

        String[] from = new String[] {NotesDbAdapter.KEY_TITLE};
        int[] to = new int[] {R.id.text1};

        SimpleCursorAdapter notes = new SimpleCursorAdapter(this, R.layout.notes_row, cursor, from, to);
        setListAdapter(notes);

        if(notes.getCount() == 0)
            emptyText.setVisibility(View.VISIBLE);
        else
            emptyText.setVisibility(View.GONE);
    }

    private void createNote()
    {
        Intent intent = new Intent(this, NoteEdit.class);
        startActivityForResult(intent, ACTIVITY_CREATE);
    }
}
