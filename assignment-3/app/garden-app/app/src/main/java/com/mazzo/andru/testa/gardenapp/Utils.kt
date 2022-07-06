package com.mazzo.andru.testa.gardenapp

import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment

class Utils {

    companion object{

        fun changeCurrentFragment(activity: AppCompatActivity, fragment: Fragment){
            val transaction = activity.supportFragmentManager.beginTransaction()
            transaction.replace(R.id.fragment_container, fragment, fragment.tag)
            transaction.addToBackStack(fragment.tag)
            transaction.commit()
        }

    }
}