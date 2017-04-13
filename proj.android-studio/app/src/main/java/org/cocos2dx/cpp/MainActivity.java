package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import com.google.common.logging.nano.Vr;

import org.cocos2dx.VRDemo.R;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends Activity implements AdapterView.OnItemClickListener{
    private final static String TAG = "MainActivity";
    private ListView mListView;
    private LocalRecordAdapter mAdapter;
    private Button mRecord;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mRecord = (Button) findViewById(R.id.local_record_button);
        mRecord.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                gotoVRMode(null);
            }
        });
        mListView = (ListView) findViewById(R.id.local_record_list);
        mListView.setOnItemClickListener(this);

        mAdapter = new LocalRecordAdapter(this, getList());
        mListView.setAdapter(mAdapter);

    }

    List<LocalSongInfo> getList() {
        List<LocalSongInfo> list = new ArrayList<>();
        LocalSongInfo info = new LocalSongInfo();
        info.songName = "埋葬冬天";
        info.songTime = "2017年4月13日10:11";
        info.weatherTag = "下雪";
        info.bgTag = "夕阳";
        info.bgType = 0;
        info.weatherType = 1;
        info.lyricFileName = "埋葬冬天.lrc";
        info.songFileName = "song.wav";

        list.add(info);
        info.bgType = 1;
        list.add(info);
        info.bgType = 2;
        list.add(info);
        info.bgType = 3;
        list.add(info);

        return list;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Log.d(TAG, position + "");
        LocalSongInfo info = mAdapter.getItem(position);
        Log.d(TAG, info.bgType + "");
        gotoVRMode(info);
    }

    private void gotoVRMode(LocalSongInfo info) {
        if (info == null) {
            //录音
            VRSongInfo.playType = 2;
            VRSongInfo.songFileName = "song.wav";
            VRSongInfo.lyricFileName = "埋葬冬天.lrc";
            VRSongInfo.weatherType = 1;
            VRSongInfo.bgType = 1;
        } else {
            //播放
            VRSongInfo.playType = 1;
            VRSongInfo.songFileName = info.songFileName;
            VRSongInfo.lyricFileName = info.lyricFileName;
            VRSongInfo.weatherType = info.weatherType;
            VRSongInfo.bgType = info.bgType;
        }
        Intent intent = new Intent(MainActivity.this, AppActivity.class);
        startActivity(intent);
        System.gc();
        System.gc();
        finish();
    }

    class LocalRecordAdapter extends BaseAdapter {
        private List<LocalSongInfo> mList = null;
        private LayoutInflater mInflater = null;
        private ViewHolder holder;

        public LocalRecordAdapter(Context context, List<LocalSongInfo> list) {
            if (list == null) {
                list = new ArrayList<>();
            }
            this.mList = list;
            this.mInflater = LayoutInflater.from(context);
        }
        @Override
        public int getCount() {
            return mList.size();
        }

        @Override
        public LocalSongInfo getItem(int position) {
            return mList.get(position);
        }

        @Override
        public long getItemId(int position) {
            return 0;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = this.mInflater.inflate(R.layout.local_record_list_item, null);
                holder = new ViewHolder(convertView);
                convertView.setTag(holder);
            } else {
                holder = (ViewHolder)convertView.getTag();
            }

            //holder 数据填充
            LocalSongInfo data = getItem(position);
            if (data != null) {
                holder.songName.setText(data.songName);
                holder.songTime.setText(data.songTime);
                holder.weatherTag.setText(data.weatherTag);
                holder.bgTag.setText(data.bgTag);
            }
            return convertView;
        }

        class ViewHolder {
            TextView songName;
            TextView songTime;
            TextView weatherTag;
            TextView bgTag;

            public ViewHolder(View convertView) {
                songName = (TextView)convertView.findViewById(R.id.song_name);
                songTime = (TextView)convertView.findViewById(R.id.song_time);
                weatherTag = (TextView)convertView.findViewById(R.id.tag_weather);
                bgTag = (TextView)convertView.findViewById(R.id.tag_background);
            }
        }
    }
}
