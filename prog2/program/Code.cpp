#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

//function prototypes
void getInput (double& initialHorizontalVelocity, double& impactAngle, double& contactHeight, bool& verifiedInput);
double fenceTime (double horizontalVelocity);
double parksEdgeTime (double horizontalVelocity);
double heightAtFence (double verticalVelocity, double fenceTime, double baseHeight);
double heightAtEdge (double verticalVelocity, double edgeTime, double baseHeight);
double maxHeight (double verticalVelocity, double baseHeight, double gravity);
double travelTime (double verticalVelocity, double gravity, double baseHeight);
double distanceTraveled (double travelTime, double horizontalVelocity);
int hitResult (double heightAtFence, double distanceToFence, double heightAtEdge, double distanceToEdge, double distanceTraveled);
void output (double distanceTraveled, double airTime, double maxHeight, int hitResult);

//constants
const double GRAVITY = 32.10;
const double DISTANCEOFFENCE = 400;
const double DISTANCEOFEDGE = 600;

int main()
{
    double initialHorizontalVelocity;
    double impactAngle;
    double contactHeight;
    bool verifiedInput;

    //Calls input function
    getInput(initialHorizontalVelocity, impactAngle, contactHeight, verifiedInput);

    //Checks to see if the user input is valid
    if(verifiedInput)
    {
        //Calls functions with actual parameters
        double initialVerticalVelocity = initialHorizontalVelocity * tan(impactAngle * M_PI /180);

        double timeToFence = fenceTime (initialHorizontalVelocity);
        double timeToEdge = parksEdgeTime (initialHorizontalVelocity);
	    double ballHeightAtFence = heightAtFence (initialVerticalVelocity, timeToFence, contactHeight);
        double ballHeightAtEdge = heightAtEdge (initialVerticalVelocity, timeToEdge, contactHeight);
        double maxBallHeight =  maxHeight (initialVerticalVelocity, contactHeight, GRAVITY);
        double ballTravelTime = travelTime (initialVerticalVelocity, GRAVITY, contactHeight);
        double distanceBallTraveled = distanceTraveled (ballTravelTime, initialHorizontalVelocity);

        int result = hitResult (ballHeightAtFence, DISTANCEOFFENCE, ballHeightAtEdge, DISTANCEOFEDGE, distanceBallTraveled);

        output (distanceBallTraveled , ballTravelTime, maxBallHeight , result);
        return 0;
    }

return 0;
}

//Collects user input, validates it, and assigns it to variables
void getInput (double& initialHorizontalVelocity, double& impactAngle, double& contactHeight, bool& verifiedInput)
{
    cout << "Please input an Intitial Horizontal Velocity, Impact Angle, and Contact Height of the bat and ball" << endl;

    //tests input to make sure the input is a number
    if(!(cin >> initialHorizontalVelocity))
    {
        cout << "Please don't enter letters of words, only numbers" << endl;
        verifiedInput = false;
    }
    else if(!(cin >> impactAngle))
    {
        cout << "Please don't enter letters of words, only numbers" << endl;
        verifiedInput = false;
    }
    else if(!(cin >> contactHeight))
    {
        cout << "Please don't enter letters of words, only numbers" << endl;
        verifiedInput = false;
    }
    else
    {
        //checks to make sure the contaact height is within range
        if((1.6 <= contactHeight) && (contactHeight <= 3.6))
        {
            verifiedInput = true;
        }
        else
        {
            verifiedInput = false;
            cout << "Make sure your contact height is between 1.6 and 3.6" << endl;
        }
    }
}

//finds the time it takes for the ball to reach the fence
double fenceTime (double horizontalVelocity)
{
    double timeToFence = DISTANCEOFFENCE / horizontalVelocity;
    return timeToFence;
}

//finds the time it takes for the ball to reach the edge of the park
double parksEdgeTime (double horizontalVelocity)
{
    double timeToEdge = DISTANCEOFEDGE / horizontalVelocity;
    return timeToEdge;
}

//finds the height of the ball at the fence
double heightAtFence (double verticalVelocity, double fenceTime, double baseHeight)
{
    double ballHeightAtFence = (verticalVelocity * fenceTime) - (0.5 * GRAVITY * pow(fenceTime, 2) + baseHeight);
    return ballHeightAtFence;
}

//finds the balls height at the edge of the park
double heightAtEdge (double verticalVelocity, double edgeTime, double baseHeight)
{
    double ballHeightAtEdge = (verticalVelocity * edgeTime) - (0.5 * GRAVITY * pow(edgeTime, 2) + baseHeight);
    return ballHeightAtEdge;
}

//finds the maximum height that the ball reaches
double maxHeight (double verticalVelocity, double baseHeight, double gravity)
{
    double maxBallHeight = baseHeight + (pow(verticalVelocity, 2) / (2 * GRAVITY) );
    return maxBallHeight;
}

//finds the total time the ball is in the air
double travelTime (double verticalVelocity, double gravity, double baseHeight)
{
    double ballTravelTime = ( (- 1 * verticalVelocity) - sqrt(pow(verticalVelocity,2) + (2 * GRAVITY * baseHeight))) / (-1 * GRAVITY);
    return ballTravelTime;
}

//finds the horizontal distance that the ball travels
double distanceTraveled (double travelTime, double horizontalVelocity)
{
    double distanceBallTraveled = travelTime * horizontalVelocity;
    return distanceBallTraveled;
}

//compares values and finds out where the ball lands
int hitResult (double heightAtFence, double distanceToFence, double heightAtEdge, double distanceToEdge, double distanceBallTraveled)
{
    int hitResult;
    
    if(heightAtEdge > 30 && distanceBallTraveled > distanceToEdge)
    {
        hitResult = 2;
    }
    else if(heightAtFence > 10 && distanceBallTraveled > distanceToFence)
    {
        hitResult = 1;
    }
    else
    {
        hitResult = 0;
    }
    return hitResult;
}

//outputs all results in two different ways
void output (double distanceTraveled, double airTime, double maxHeight, int hitResult)
{
    ofstream outData;
    outData.open("Output.txt");

    outData << fixed << showpoint;
    outData << setprecision(2);

    cout << fixed << showpoint;
    cout << setprecision(2);

    outData << "The ball traveled " << distanceTraveled << " feet" << endl;
    outData << "The ball was in the air for " << airTime << " seconds" << endl;
    outData << "The ball reached a max height of " << maxHeight << " feet" << endl;
    
    cout << endl;
    cout << "-- !RESULTS! --" << endl;
    cout << "The ball traveled " << distanceTraveled << " feet" << endl;
    cout << "The ball was in the air for " << airTime << " seconds" << endl;
    cout << "The ball reached a max height of " << maxHeight << " feet" << endl;

    if(hitResult == 0)
    {
        outData << "The hit stayed within the field" << endl;
        cout << "The hit stayed within the field" << endl;
    }
    else if(hitResult == 1)
    {
        outData << "The hit was a HOME-RUN!" << endl;
        cout << "The hit was a HOME-RUN!" << endl;

    }
    else
    {
        outData << "The hit was OUT OF THE PARK!" << endl;
        cout << "The hit was OUT OF THE PARK!" << endl;
    }

    outData.close();
}