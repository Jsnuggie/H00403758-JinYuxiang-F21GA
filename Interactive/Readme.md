There are pedestrians walking on the scene. There are two rows of houses on both sides of the road.
Man is made of a sphere and a cylinder. Divided into head, body arms and legs. Build from top to bottom. Use PushMatrix to record the current position, and use PopMatrix after constructing the head. Then use the Translate position to narrowly build the body, arms, and legs in sequence. <br>
![image](https://user-images.githubusercontent.com/115422304/205988457-5777efa0-d5b3-412d-8102-9167680fcf79.png) <br>
Get the current time through glfwGetTime, and calculate the current time sin value multiplied by 30. Get a rotation angle of -30 degrees to 30 degrees. At the level of the arm joints, Rotate is used to render the arm to realize the arm swing animation. At the leg level, use Rotate to rotate the leg to realize the step animation. At the same time, use Translate to set the overall Y value to achieve the effect of walking up and down bumps. Use Translate to achieve a looping animation. <br>
![image](https://user-images.githubusercontent.com/115422304/205988744-a7396123-cb5b-4b6c-a42a-24f6d8f0e7e0.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205988788-fc9c2089-60f2-46fe-a7d6-24f478d94163.png) <br>
House is composed of sphere, cylinder, and cube. Divided into the main body, doors, windows, and top parts. The theme building uses concrete textures. Use loadImage to load bmp images. Use BindTexture to enable the texture. The window has a bay window. The window uses a black material with only ambient light to prevent the influence of light. The door uses a material with only ambient light. The stairs use marble texture. Use multiple cubes to build steps. There is a sunshade on the door. The roof is constructed with an ellipsoid, and the cylinder is connected to the main body of the house. <br>
![image](https://user-images.githubusercontent.com/115422304/205989058-cbec2311-4b51-4063-b8ca-df851865cc33.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205989068-240ff581-83a4-4f8f-a07f-7b30cdc53473.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205989104-ea14f11d-4048-431a-b47e-f50b9c4e38d7.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205989131-6a8a95c2-23ad-4944-a7b2-9b8801b6db3d.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205989165-1b131334-3d44-4151-bb25-b9f3433abc45.png) <br>
Use Skybox to render the sky. Draw a large cube facing the inside, and use six pictures to paste on the six faces. <br>
![image](https://user-images.githubusercontent.com/115422304/205989495-90806fc9-b47b-4329-8a00-63a739195632.png) <br>
The scene uses two light sources, one of which is a point light source to illuminate the entire scene. There is also a spotlight in front of a house, forming a red light source. <br>
![image](https://user-images.githubusercontent.com/115422304/205989624-7f326afa-3f92-4158-b4bb-1700a53fee93.png) <br>
![image](https://user-images.githubusercontent.com/115422304/205989645-ad6c05cf-6611-4a50-88ab-377b81115a93.png) <br>
Use W key, A key, S key, and D key to control the angle of view translation, and click and drag the mouse to control the angle of view rotation. Realized in the setCamera function. Record the camera position by modifying the GL_MODELVIEW matrix, and call Translate to move the camera. <br>
