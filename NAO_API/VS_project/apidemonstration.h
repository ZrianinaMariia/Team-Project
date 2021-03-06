#ifndef APIDEMONSTRATION_H
#define APIDEMONSTRATION_H

#include <iostream>
#include <string>
#include <vector>

//#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

#include <qi/log.hpp>
#include <qi/os.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <althread/alcriticalsection.h>
#include <alvalue/alvalue.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>

#include <alproxies/almemoryproxy.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alnavigationproxy.h>
#include <alproxies/alphotocaptureproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alvideodeviceproxy.h>
#include <alproxies/alredballdetectionproxy.h>
#include <alproxies/alfacedetectionproxy.h>
#include <alproxies/aldarknessdetectionproxy.h>

#include <althread/almutex.h>
#include <alerror/alerror.h>

namespace AL {
    // This is a forward declaration of AL:ALBroker which
    // avoids including <alcommon/albroker.h> in this header
    class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable or as a plugin within NAOqi
 */
class APIDemonstration : public AL::ALModule {
public:
    APIDemonstration(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);

    virtual ~APIDemonstration();

    /** Overloading ALModule::init().
    * This is called right after the module has been loaded
    */
    virtual void init();

    void show_postures();
    void move(const float& x, const float& y, const float& theta);
    /** IMPORTANT: 
    * If you want to make a method publicly available
    * through BIND_METHOD, all arguments should be typed
    * according to "const T&".
    */
    bool move_navigation(const float& x, const float& y, const float& theta);
    void rest();
    void wake_up();
    void posture(const std::string& posture_name);
    void take_picture(const std::string& filename);
    void disagree();
    void agree();
    void say_phrase(const std::string& phrase, const std::string& language = "English");
    void move_joints(const AL::ALValue& joints,
                     const AL::ALValue& target_angles,
                     const AL::ALValue& target_times,
                     const bool &restore_pos = false,
                     const std::string& phrase = "",
                     const float& phrase_lag = 0.0f);
    void not_these_droids();
    void bow();

    void script();

    void on_right_bumper_pressed();
    void subscribe_to_event();
    void unsubscribe_to_event();
    void onRightBumperPressed();
    void _get_control(bool *die);
    void get_visual();

    bool detect_red_ball(const float& time = 1.0);
    void red_ball_detected();

    bool detect_obstacle(const float& time = 1.0);
    void obstacle_detected(const std::string& eventName, 
                           const float& dist, 
                           const std::string& subscriberIdentifier);
    
    void face_detection();
    void face_detected();
    void stop_face_detection();

    void darkness_detection(const int &threshold = 60);
    void darkness_detected();
    void stop_darkness_detection();
    bool is_it_a_face(int time = 10); // time is in seconds

private:
    AL::ALMemoryProxy       memory_proxy;
    AL::ALTextToSpeechProxy TTS_proxy;
    AL::ALRobotPostureProxy posture_proxy;
    AL::ALMotionProxy       motion_proxy;
    AL::ALNavigationProxy   navigation_proxy;
    //AL::ALPhotoCaptureProxy photo_proxy;
    AL::ALVideoDeviceProxy  video_proxy;
    //AL::ALDarknessDetectionProxy darkness_proxy;

    float haste;

    bool b_red_ball_detected;
    bool b_face_detected;
    bool b_obstacle_detected;

    boost::shared_ptr<AL::ALMutex> fCallbackMutexBumper;
    boost::shared_ptr<AL::ALMutex> fCallbackMutexFaceDetection;
    boost::shared_ptr<AL::ALMutex> fCallbackMutexDarknessDetection;
    boost::shared_ptr<AL::ALMutex> fCallbackMutexRedBallDetection;
    boost::shared_ptr<AL::ALMutex> fCallbackMutexObstacleDetection;
};
#endif // APIDEMONSTRATION_H
