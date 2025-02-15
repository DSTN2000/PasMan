package org.pas.man;

import org.qtproject.qt.android.bindings.QtActivity;
import android.os.Bundle;
import android.view.View;
import android.graphics.Color;
import android.view.Window;
import android.view.WindowManager;

public class PasManActivity extends QtActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Set the status bar color to white
        Window window = getWindow();
        window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
        window.setStatusBarColor(Color.WHITE);

        // Set system bar icons to dark (for better visibility on white background)
        window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR);

    }
}
