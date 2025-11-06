#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <opencv2/core.hpp>
#include "eyerec/PuRe.hpp"
#include "eyerec/PuReST.hpp"
#include "eyerec/Pupil.hpp"

namespace py = pybind11;

// Helper function to convert numpy array to cv::Mat
cv::Mat numpy_to_mat(py::array_t<unsigned char> input) {
    py::buffer_info buf = input.request();
    
    if (buf.ndim == 2) {
        // Grayscale image
        return cv::Mat(buf.shape[0], buf.shape[1], CV_8UC1, buf.ptr);
    } else if (buf.ndim == 3 && buf.shape[2] == 3) {
        // BGR image
        return cv::Mat(buf.shape[0], buf.shape[1], CV_8UC3, buf.ptr);
    } else {
        throw std::runtime_error("Invalid array shape. Expected 2D grayscale or 3D BGR image.");
    }
}

// Python wrapper class for PuRe
class PyPuRe {
private:
    PuRe detector;
    
public:
    PyPuRe() : detector() {}
    
    // Detect pupil from numpy array
    py::dict detect(py::array_t<unsigned char> frame_array) {
        cv::Mat frame = numpy_to_mat(frame_array);
        
        DetectionParameters params;
        Pupil pupil = detector.detect(frame, params);
        
        // Convert Pupil result to Python dictionary
        py::dict result;
        result["center_x"] = pupil.center.x;
        result["center_y"] = pupil.center.y;
        result["width"] = pupil.size.width;
        result["height"] = pupil.size.height;
        result["angle"] = pupil.angle;
        result["confidence"] = pupil.confidence;
        result["valid"] = pupil.valid();
        
        return result;
    }
    
    // Detect with custom parameters
    py::dict detect_with_params(py::array_t<unsigned char> frame_array,
                                 py::dict params_dict) {
        cv::Mat frame = numpy_to_mat(frame_array);
        
        DetectionParameters params;
        
        // Parse ROI if provided
        if (params_dict.contains("roi")) {
            py::tuple roi = params_dict["roi"].cast<py::tuple>();
            if (roi.size() == 4) {
                params.roi = cv::Rect(
                    roi[0].cast<int>(),
                    roi[1].cast<int>(),
                    roi[2].cast<int>(),
                    roi[3].cast<int>()
                );
            }
        }
        
        // Parse min/max pupil diameter if provided
        if (params_dict.contains("min_pupil_diameter")) {
            params.userMinPupilDiameterPx = params_dict["min_pupil_diameter"].cast<float>();
        }
        if (params_dict.contains("max_pupil_diameter")) {
            params.userMaxPupilDiameterPx = params_dict["max_pupil_diameter"].cast<float>();
        }
        if (params_dict.contains("provide_confidence")) {
            params.provideConfidence = params_dict["provide_confidence"].cast<bool>();
        }
        
        Pupil pupil = detector.detect(frame, params);
        
        // Convert Pupil result to Python dictionary
        py::dict result;
        result["center_x"] = pupil.center.x;
        result["center_y"] = pupil.center.y;
        result["width"] = pupil.size.width;
        result["height"] = pupil.size.height;
        result["angle"] = pupil.angle;
        result["confidence"] = pupil.confidence;
        result["valid"] = pupil.valid();
        
        return result;
    }
    
    std::string get_description() {
        return detector.description();
    }
};

// Python wrapper class for PuReST (tracking)
class PyPuReST {
private:
    PuReST tracker;
    Timestamp current_ts;
    
public:
    PyPuReST() : tracker(), current_ts(0) {}
    
    // Detect and track pupil from numpy array
    py::dict detect_and_track(py::array_t<unsigned char> frame_array, 
                               double timestamp = -1.0) {
        cv::Mat frame = numpy_to_mat(frame_array);
        
        // Use provided timestamp or auto-increment
        if (timestamp >= 0) {
            current_ts = static_cast<Timestamp>(timestamp);
        } else {
            current_ts += 16.67;  // Assume ~60fps if not provided
        }
        
        TrackingParameters params;
        Pupil pupil = tracker.detectAndTrack(current_ts, frame, params);
        
        // Convert Pupil result to Python dictionary
        py::dict result;
        result["center_x"] = pupil.center.x;
        result["center_y"] = pupil.center.y;
        result["width"] = pupil.size.width;
        result["height"] = pupil.size.height;
        result["angle"] = pupil.angle;
        result["confidence"] = pupil.confidence;
        result["valid"] = pupil.valid();
        
        return result;
    }
    
    // Detect and track with custom parameters
    py::dict detect_and_track_with_params(py::array_t<unsigned char> frame_array,
                                           py::dict params_dict,
                                           double timestamp = -1.0) {
        cv::Mat frame = numpy_to_mat(frame_array);
        
        // Use provided timestamp or auto-increment
        if (timestamp >= 0) {
            current_ts = static_cast<Timestamp>(timestamp);
        } else {
            current_ts += 16.67;
        }
        
        TrackingParameters params;
        
        // Parse ROI if provided
        if (params_dict.contains("roi")) {
            py::tuple roi = params_dict["roi"].cast<py::tuple>();
            if (roi.size() == 4) {
                params.roi = cv::Rect(
                    roi[0].cast<int>(),
                    roi[1].cast<int>(),
                    roi[2].cast<int>(),
                    roi[3].cast<int>()
                );
            }
        }
        
        // Parse tracking-specific parameters
        if (params_dict.contains("max_age")) {
            params.maxAge = params_dict["max_age"].cast<Timestamp>();
        }
        if (params_dict.contains("min_detection_confidence")) {
            params.minDetectionConfidence = params_dict["min_detection_confidence"].cast<float>();
        }
        if (params_dict.contains("min_pupil_diameter")) {
            params.userMinPupilDiameterPx = params_dict["min_pupil_diameter"].cast<float>();
        }
        if (params_dict.contains("max_pupil_diameter")) {
            params.userMaxPupilDiameterPx = params_dict["max_pupil_diameter"].cast<float>();
        }
        
        Pupil pupil = tracker.detectAndTrack(current_ts, frame, params);
        
        // Convert Pupil result to Python dictionary
        py::dict result;
        result["center_x"] = pupil.center.x;
        result["center_y"] = pupil.center.y;
        result["width"] = pupil.size.width;
        result["height"] = pupil.size.height;
        result["angle"] = pupil.angle;
        result["confidence"] = pupil.confidence;
        result["valid"] = pupil.valid();
        
        return result;
    }
    
    std::string get_description() {
        return tracker.description();
    }
};

PYBIND11_MODULE(pyeyerec, m) {
    m.doc() = "Python bindings for eyerec pupil detection library";
    
    py::class_<PyPuRe>(m, "PuRe")
        .def(py::init<>(), "Create a new PuRe pupil detector")
        .def("detect", &PyPuRe::detect,
             "Detect pupil in a frame (numpy array)",
             py::arg("frame"))
        .def("detect_with_params", &PyPuRe::detect_with_params,
             "Detect pupil with custom parameters",
             py::arg("frame"),
             py::arg("params"))
        .def("description", &PyPuRe::get_description,
             "Get detector description");
    
    py::class_<PyPuReST>(m, "PuReST")
        .def(py::init<>(), "Create a new PuReST pupil tracker")
        .def("detect_and_track", &PyPuReST::detect_and_track,
             "Detect and track pupil in a frame (numpy array)",
             py::arg("frame"),
             py::arg("timestamp") = -1.0)
        .def("detect_and_track_with_params", &PyPuReST::detect_and_track_with_params,
             "Detect and track pupil with custom parameters",
             py::arg("frame"),
             py::arg("params"),
             py::arg("timestamp") = -1.0)
        .def("description", &PyPuReST::get_description,
             "Get tracker description");
}
