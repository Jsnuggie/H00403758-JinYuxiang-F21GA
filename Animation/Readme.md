# __Export fbx file__</br>
![image](https://user-images.githubusercontent.com/115422304/201389481-9c9c8e16-a28c-49da-9104-c0bbee81b380.png)
# __Adjust the material__</br>
After importing the fbx scene, the materials of the model are a bit strange, I rescaled these materials.
![Screenshot 2022-11-10 190641](https://user-images.githubusercontent.com/115422304/201389175-bf08746a-6e44-4eed-bf6f-223e625f5d2b.png)</br>
# __Animation__</br>
I first created an empty object as the parent of the tree, bushes, house, street light, fence, road and white line of the road, pulled the last part of the road to the position of the first frame of the car, and gave a keyframe to set the time Adjust the axis to frame 300, pull the front part of the road to the position of the car, give a keyframe, and create a linear animation.</br>
To animate the car shaking, I bound the parts except the tires to an empty block object, then keyframed the first frame, added a noise modifier on the Z axis, and adjusted the intensity and frequency. The animation of the exhaust is a particle effect emitted by a plane on the back of the car.</br>
