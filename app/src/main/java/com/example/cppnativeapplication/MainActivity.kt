package com.example.cppnativeapplication

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.cppnativeapplication.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.sampleText.text =
            writeToFile(dataDir.absolutePath + "/file.txt", "My name is Tejas 2")
        binding.sampleFileContent.text = readFile(dataDir.absolutePath + "/file.txt")
    }

    private external fun getInternalPath(): String

    private external fun writeToFile(path: String, text: String): String

    private external fun readFile(path: String): String

    companion object {
        // Used to load the 'cppnativeapplication' library on application startup.
        init {
            System.loadLibrary("cppnativeapplication")
        }
    }
}