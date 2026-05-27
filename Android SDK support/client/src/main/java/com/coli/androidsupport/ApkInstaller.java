package com.coli.androidsupport;

import android.app.AlertDialog;
import android.app.DownloadManager;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import androidx.core.content.FileProvider;

import java.io.File;
import java.io.IOException;

public class ApkInstaller {
    private Context mContext;
    private DownloadManager downloadManager;
    private DownloadProgressDialog progressDialog;
    private String storageFile;
    private String name;
    private long downloadId;
    private final QueryRunnable mQueryProgressRunnable = new QueryRunnable();
    private final StatusRunnable mQueryStatusRunnable = new StatusRunnable();
    private final int RETRIES_MAX_NUMBER = 3;
    private int retriseCount = 0;


    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if (msg.what == 1001) {
                if (progressDialog != null) {
                    progressDialog.setProgress(msg.arg1);
                    progressDialog.setMax(msg.arg2);
                }
            }
        }
    };

    public ApkInstaller(Context ctx, String url) {
        this.mContext = ctx;
        downloadAPK(url);
    }

    // 下载APk
    private void downloadAPK(final String url) {
        try {
            // 获取文件名
            String filename = url.substring(url.lastIndexOf("/")+1, url.length());
            this.name = filename;

            DownloadManager.Request req = new DownloadManager.Request(Uri.parse(url));
            // 通知栏可见
            req.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
            //通知栏标题
            req.setTitle("提示");
            //通知栏描述信息
            req.setDescription("更新包");

            // 设置允许的网络类型
            req.setAllowedNetworkTypes(DownloadManager.Request.NETWORK_MOBILE|DownloadManager.Request.NETWORK_WIFI);

            // 设置下载路径和保存路径
            File file = new File(mContext.getExternalFilesDir(Environment.DIRECTORY_DOWNLOADS), filename);
            req.setDestinationUri(Uri.fromFile(file));
            storageFile = file.getAbsolutePath();

            // 获取DownloadManger
            if (downloadManager == null)
                downloadManager = (DownloadManager) mContext.getSystemService(Context.DOWNLOAD_SERVICE);

            if (downloadManager != null)
                downloadId = downloadManager.enqueue(req);

            //设置类型为.apk
            req.setMimeType("application/vnd.android.package-archive");

            // 注册广播接受者，监听下载状态
            mContext.registerReceiver(receiver,
                    new IntentFilter(DownloadManager.ACTION_DOWNLOAD_COMPLETE));
            mContext.registerReceiver(receiver,
                    new IntentFilter(DownloadManager.ACTION_NOTIFICATION_CLICKED));

            // 开始查询进度
            startQueryProgress();
            // 开始查询状态
            startQueryStatus();
            displayProgressDialog();
        } catch (Exception ex) {
            Toast.makeText(mContext, "找不到下载文件", Toast.LENGTH_SHORT).show();
        }

    }

    //进入下载详情
    private void showDownloadDetail() {
        Intent intent = new Intent(DownloadManager.ACTION_VIEW_DOWNLOADS);
        if(intent.resolveActivity(mContext.getPackageManager())!=null){
            mContext.startActivity(intent);
        }
    }

    // 查询进度
    private void startQueryProgress() {
        if (downloadId != 0) {
            mHandler.post(mQueryProgressRunnable);
        }
    }

    private void startQueryStatus() {
        if (downloadId != 0) {
            mHandler.post(mQueryStatusRunnable);
        }
    }

    private void displayProgressDialog() {
        if (progressDialog == null) {
            // 创建ProgressDialog对象
            progressDialog = new DownloadProgressDialog(mContext);
            // 设置进度条风格，风格为长形
            progressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
            // 设置ProgressDialog 标题
            progressDialog.setTitle("下载提示");
            // 设置ProgressDialog 提示信息
            progressDialog.setMessage("当前下载进度:");
            // 设置ProgressDialog 的进度条是否不明确
            progressDialog.setIndeterminate(false);
            // 设置ProgressDialog 是否可以按退回按键取消
            progressDialog.setCancelable(false);
//            progressDialog.setProgressDrawable(mContext.getResources().getDrawable(R.drawable.download_progressdrawable));
//            progressDialog.setButton(DialogInterface.BUTTON_NEGATIVE, "取消", new DialogInterface.OnClickListener() {
//                @Override
//                public void onClick(DialogInterface dialog, int which) {
////                    removeDownload();
//                    dialog.dismiss();
////                    finish();
//                }
//            });
        }
        if (!progressDialog.isShowing()) {
            // 让ProgressDialog显示
            progressDialog.show();
        }
    }

    // 广播接收者
    private BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (DownloadManager.ACTION_NOTIFICATION_CLICKED.equals(action)) {
                showDownloadDetail();
            } else if (DownloadManager.ACTION_DOWNLOAD_COMPLETE.equals(action)) {
                checkStatus();
            }
        }
    };

    //查询下载进度
    private class QueryRunnable implements Runnable {
        @Override
        public void run() {
            checkProgress();
        }
    }

    private class StatusRunnable implements Runnable {
        @Override
        public void run() {
            checkStatus();
        }
    }

    private void removeAllRunnable() {
        mHandler.removeCallbacksAndMessages(mQueryProgressRunnable);
        mHandler.removeCallbacksAndMessages(mQueryStatusRunnable);
    }

    private void checkProgress() {
        // 通过ID向下载管理查询下载情况，返回一个cursor
        DownloadManager.Query query = new DownloadManager.Query();
        query.setFilterById(downloadId);
        Boolean isContinue = true;

        Cursor cursor = downloadManager.query(query);
        if (cursor == null) {
            showFailedMsg();
            isContinue = false;
        } else { // 以下是从游标中进行信息提取
            if (cursor.moveToFirst()) {
                int soFar = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_BYTES_DOWNLOADED_SO_FAR));
                int total = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_TOTAL_SIZE_BYTES));
                Log.d("Download", "Progress=" + String.valueOf(soFar) + "/" + String.valueOf(total));

                // 同步进度到ui
                if(total > 0) {
                    Message msg = new Message();
                    msg.what = 1001;
                    msg.arg1 = soFar;
                    msg.arg2 = total;
                    mHandler.sendMessage(msg);
                }
            } else {
                showFailedMsg();
                isContinue = false;
            }

            if(!cursor.isClosed()){
                cursor.close();
            }
        }

        if (isContinue) {
            mHandler.postDelayed(mQueryProgressRunnable,100);
        }
    }

    private void showFailedMsg() {
        AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(mContext);
        dlgAlert.setMessage("无法正确下载升级包！");
        dlgAlert.setTitle("提示");
        dlgAlert.setPositiveButton("确认", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                closeApp();
            }
        });
        dlgAlert.setCancelable(true);
        dlgAlert.create().show();
    }

    private void closeApp() {
        android.os.Process.killProcess(android.os.Process.myPid());
    }

    // 状态监测
    private void checkStatus() {
        DownloadManager.Query query = new DownloadManager.Query();
        Boolean isContinue = true;

        //通过下载的id查找
        query.setFilterById(downloadId);
        query.setFilterByStatus(DownloadManager.STATUS_PAUSED | DownloadManager.STATUS_PENDING | DownloadManager.STATUS_SUCCESSFUL);
        Cursor cursor = downloadManager.query(query);
        if (cursor.moveToFirst()) {
            int status = cursor.getInt(cursor.getColumnIndex(DownloadManager.COLUMN_STATUS));
            Log.d("Test", "status = " + String.valueOf(status));
            switch (status) {
                //下载暂停
                case DownloadManager.STATUS_PAUSED:
                    retriseCount++;
                    if (retriseCount >= RETRIES_MAX_NUMBER) {
//                        Toast.makeText(mContext, "下载失败, 确认退出", Toast.LENGTH_SHORT).show();
                        showFailedMsg();
                        isContinue = false;
                    }
                    break;
                //下载延迟
                case DownloadManager.STATUS_PENDING:
                    break;
                //正在下载
                case DownloadManager.STATUS_RUNNING:
                    break;
                //下载完成
                case DownloadManager.STATUS_SUCCESSFUL:
                    //下载完成安装APK
                    installAPK();

                    // 停止查询进度，因为已经下载好了
                    removeAllRunnable();
                    closeApp();
                    isContinue = false;
                    break;
                //下载失败
                case DownloadManager.STATUS_FAILED:
                    showFailedMsg();
                    mContext.unregisterReceiver(receiver);
                    removeAllRunnable();
                    isContinue = false;
                    break;
            }
        } else {
            Toast.makeText(mContext, "下载失败", Toast.LENGTH_SHORT).show();
            isContinue = false;
        }

        if(!cursor.isClosed()){
            cursor.close();
        }

        if (isContinue) {
            mHandler.postDelayed(mQueryStatusRunnable,5000);
        }
    }

    // 安装Apk
    private void installAPK() {
        setPermission(storageFile);
        Intent intent = new Intent(Intent.ACTION_VIEW);
        // 由于没有在Activity环境下启动Activity,设置下面的标签
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        //Android 7.0以上要使用FileProvider
        if (Build.VERSION.SDK_INT >= 24) {
            File file = (new File(storageFile));
            //参数1 上下文, 参数2 Provider主机地址 和配置文件中保持一致   参数3  共享的文件
            Uri apkUri =  FileProvider.getUriForFile(mContext, "com.lxtwsw.weather.fileprovider", file);
            //添加这一句表示对目标应用临时授权该Uri所代表的文件
            intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
            intent.setDataAndType(apkUri, "application/vnd.android.package-archive");
        } else {
            Uri uri =  Uri.fromFile(new File(storageFile));
            intent.setDataAndType(uri, "application/vnd.android.package-archive");
        }
        mContext.startActivity(intent);
    }

    //修改文件权限
    private void setPermission(String absolutePath) {
        String command = "chmod " + "777" + " " + absolutePath;
        Runtime runtime = Runtime.getRuntime();
        try {
            runtime.exec(command);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
