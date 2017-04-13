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
import android.widget.ListView;
import android.widget.TextView;

import org.cocos2dx.VRDemo.R;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends Activity implements AdapterView.OnItemClickListener{
    private final static String TAG = "MainActivity";
    private ListView mListView;
    private LocalRecordAdapter mAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

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

        list.add(info);
        list.add(info);
        list.add(info);
        list.add(info);

        return list;

    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Log.d(TAG, position + "");
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
