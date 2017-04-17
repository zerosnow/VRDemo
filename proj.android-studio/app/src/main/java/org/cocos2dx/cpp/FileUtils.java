package org.cocos2dx.cpp;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by archerlei on 2017/4/17.
 */

public class FileUtils {
    private static final String TAG = "FileUtils";
    private static SQLiteDatabase mDatabase;

    public static void init(Context context) {

        mDatabase = SQLiteDatabase.openOrCreateDatabase(context.getFilesDir().getPath() + "songInfo.db", null);
        mDatabase.execSQL("create table if not exists songInfo (songFileName TEXT, lyricFileName TEXT, weatherType INTEGER, bgType INTEGER, songName TEXT, songTime TEXT, weatherTag TEXT, bgTag TEXT)");
    }
    public static void storeFileFromC(String songFileName, String lyricFileName, int weatherType, int bgType, String songName, String songTime, String weatherTag, String bgTag) {
        Log.d(TAG, songFileName + " " + lyricFileName + " " + weatherType + " " + bgType + " " + songName + " " + songTime + " " + weatherTag + " " + bgTag);
        if (mDatabase != null) {
            ContentValues cv = new ContentValues();
            cv.put("songFileName", songFileName);
            cv.put("lyricFileName", lyricFileName);
            cv.put("weatherType", weatherType);
            cv.put("bgType", bgType);
            cv.put("songName", songName);
            cv.put("songTime", songTime);
            cv.put("weatherTag", weatherTag);
            cv.put("bgTag", bgTag);
            mDatabase.insert("songInfo", null, cv);
        } else {
            Log.d(TAG, "mDatabase is null");
        }
    }

    public static List<LocalSongInfo> getSongInfo() {
        List<LocalSongInfo> songInfoList = new ArrayList<>();
        Cursor c = mDatabase.rawQuery("select * from songInfo", null);
        while(c.moveToNext()) {
            LocalSongInfo info = new LocalSongInfo();
            info.songFileName = c.getString(c.getColumnIndex("songFileName"));
            info.lyricFileName = c.getString(c.getColumnIndex("lyricFileName"));
            info.weatherType = c.getInt(c.getColumnIndex("weatherType"));
            info.bgType = c.getInt(c.getColumnIndex("bgType"));
            info.songName = c.getString(c.getColumnIndex("songName"));
            info.songTime = c.getString(c.getColumnIndex("songTime"));
            info.weatherTag = c.getString(c.getColumnIndex("weatherTag"));
            info.bgTag = c.getString(c.getColumnIndex("bgTag"));
            songInfoList.add(info);
        }
        c.close();
        return songInfoList;
    }
}
