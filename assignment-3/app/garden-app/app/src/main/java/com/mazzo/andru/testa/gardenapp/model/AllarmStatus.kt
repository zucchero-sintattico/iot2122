package com.mazzo.andru.testa.gardenapp.model

import android.util.Log
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.fuel.httpPost
import com.github.kittinunf.result.Result

class AllarmStatus(ip : String) {

    private val completeUrl = "http://$ip/status"

    fun getAllarmStatus(callback: (String) -> Unit) : Boolean{
        val httpAsync = completeUrl
            .httpGet()
            .responseString { request, response, result ->
                when (result) {
                    is Result.Failure -> {
                        val ex = result.getException()
                        Log.d("request", ex.toString())
                    }
                    is Result.Success -> {
                        val data = result.get()
                        callback(data)
                        Log.d("request", data)
                    }
                }
            }
        httpAsync.join()

        return false
    }

    fun setManualMode(){
        val httpAsync = completeUrl
            .httpPost()
            .body("MANUAL")
            .responseString { request, response, result ->
                when (result) {
                    is Result.Failure -> {
                        val ex = result.getException()
                        Log.d("request", ex.toString())
                    }
                    is Result.Success -> {
                        val data = result.get()
                        Log.d("request", data)
                    }
                }
            }
        httpAsync.join()
    }

    fun setAutoMode(){
        val httpAsync = completeUrl
            .httpPost()
            .body("AUTO")
            .responseString { request, response, result ->
                when (result) {
                    is Result.Failure -> {
                        val ex = result.getException()
                        Log.d("request", ex.toString())
                    }
                    is Result.Success -> {
                        val data = result.get()
                        Log.d("request", data)
                    }
                }
            }
        httpAsync.join()
    }
}