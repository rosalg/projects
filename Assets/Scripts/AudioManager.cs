using System.Collections;
using System.Collections.Generic;
using UnityEngine.Audio;
using UnityEngine;
using System;
using UnityEngine.UI;

public class AudioManager : MonoBehaviour
{
    public Sound[] sounds;
    public static AudioManager instance = null;

    public Slider slider;

    private AudioSource backgroundMusic;

    // Start is called before the first frame update
    void Awake()
    {

        if (Resources.FindObjectsOfTypeAll<Slider>().Length != 0)
        {
            slider = Resources.FindObjectsOfTypeAll<Slider>()[0];
            slider.onValueChanged.AddListener(AdjustVolume);
            AdjustVolume(slider.value);
        }
        

        if (instance == null)
        {
            instance = this;
        } else
        {
            Destroy(gameObject);
            return;
        }

        DontDestroyOnLoad(gameObject);

        foreach (Sound s in sounds)
        {
            s.source = gameObject.AddComponent<AudioSource>();
            s.source.clip = s.clip;
            s.source.name = s.name;

            s.source.volume = s.volume;
            s.source.pitch = s.pitch;

            s.source.loop = s.loop;

            if (s.name == "BackgroundMusic")
            {
                backgroundMusic = s.source;
            }
        }
    }

    private void Start()
    {
        Play("BackgroundMusic");
    }

    public void Play(string name)
    {
        Sound s = Array.Find(sounds, sound => sound.name == name);
        if (s == null)
        {
            Debug.LogWarning("Song of name " + name + " was not found.");
        }
        s.source.Play();
    }

    public void AdjustVolume(float value)
    {
        if (backgroundMusic != null)
        {
            backgroundMusic.volume = value;
        }
        
    }
}
