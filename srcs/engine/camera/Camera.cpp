#include <engine/camera/Camera.hpp>

//**** STATIC FUNCTIONS DEFINE *************************************************
//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------

Camera::Camera(void)
{
	this->winRatio = (float)WIN_W / (float)WIN_H;
	this->fov = FOV;

	this->projection = gm::Mat4f::perspective(gm::radians(this->fov), this->winRatio, NEAR, FAR);

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;

	this->position = gm::Vec3f(0.0f, 0.0f, 0.0f);
	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

	this->computeRotation();
	this->computeView();
}


Camera::Camera(const Camera &obj)
{
	this->view = obj.view;
	this->projection = obj.projection;
	this->position = obj.position;
	this->front = obj.front;
	this->up = obj.up;
	this->right = obj.right;
	this->pitch = obj.pitch;
	this->yaw = obj.yaw;
	this->roll = obj.roll;
	this->planeWidth = obj.planeWidth;
	this->planeHeight = obj.planeHeight;
	this->winRatio = obj.winRatio;
}

//---- Destructor --------------------------------------------------------------

Camera::~Camera()
{

}

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------

const gm::Mat4f	&Camera::getProjection(void) const
{
	return (this->projection);
}


const gm::Mat4f	&Camera::getView(void) const
{
	return (this->view);
}


const gm::Vec3f	&Camera::getPosition(void) const
{
	return (this->position);
}


const gm::Vec3f	&Camera::getFront(void) const
{
	return (this->front);
}


const gm::Vec3f	&Camera::getUp(void) const
{
	return (this->up);
}


const gm::Vec3f	&Camera::getRight(void) const
{
	return (this->right);
}


float	Camera::getPitch(void) const
{
	return (this->pitch);
}


float	Camera::getYaw(void) const
{
	return (this->yaw);
}


float	Camera::getRoll(void) const
{
	return (this->roll);
}

//---- Setters -----------------------------------------------------------------

void	Camera::setPosition(const gm::Vec3f &position)
{
	this->position = position;
	this->computeView();
}


void	Camera::setRotation(const float pitch, const float yaw, const float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->computeRotation();
	this->computeView();
}

//---- Operators ---------------------------------------------------------------

Camera	&Camera::operator=(const Camera &obj)
{
	if (this == &obj)
		return (*this);

	this->view = obj.view;
	this->projection = obj.projection;
	this->position = obj.position;
	this->front = obj.front;
	this->up = obj.up;
	this->right = obj.right;
	this->pitch = obj.pitch;
	this->yaw = obj.yaw;
	this->roll = obj.roll;
	this->planeWidth = obj.planeWidth;
	this->planeHeight = obj.planeHeight;
	this->winRatio = obj.winRatio;

	return (*this);
}

//**** PUBLIC METHODS **********************************************************
//---- move --------------------------------------------------------------------

void	Camera::move(const gm::Vec3f &direction, const float speed)
{
	this->position += this->right * direction.x * speed
						+ this->up * direction.y * speed
						+ this->front * direction.z * speed;
	this->computeView();
}


void	Camera::moveFront(const float speed)
{
	this->position += this->front * speed;
	this->computeView();
}


void	Camera::moveUp(const float speed)
{
	this->position += this->up * speed;
	this->computeView();
}


void	Camera::moveRight(const float speed)
{
	this->position += this->right * speed;
	this->computeView();
}

//---- rotate ------------------------------------------------------------------

void	Camera::rotateX(const float degrees)
{
	this->pitch += degrees;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->computeRotation();
	this->computeView();
}


void	Camera::rotateY(const float degrees)
{
	this->yaw += degrees;
	this->computeRotation();
	this->computeView();
}


void	Camera::rotateZ(const float degrees)
{
	this->roll += degrees;
	this->computeRotation();
	this->computeView();
}

//---- update ------------------------------------------------------------------

void	Camera::updateFromWindow(const int windowWidth, const int windowHeight)
{
	this->winRatio = (float)windowWidth / (float)windowHeight;

	this->projection = gm::Mat4f::perspective(gm::radians(this->fov), this->winRatio, NEAR, FAR);

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;
}


void	Camera::updateFOV(const float fov)
{
	this->fov = fov;

	if (this->fov < 0.0f)
		this->fov = 0.0f;
	if (this->fov > 360.0f)
		this->fov = 360.0f;

	this->projection = gm::Mat4f::perspective(gm::radians(this->fov), this->winRatio, NEAR, FAR);

	this->planeHeight = tan(gm::radians(this->fov * 0.5f)) * 2.0f;
	this->planeWidth = this->planeHeight * this->winRatio;
}

//---- status ------------------------------------------------------------------

void	Camera::printStatus(void)
{
	std::cout << "Camera status\n  position : " << this->position
				<< "\n  pitch : " << this->pitch
				<< ", yaw : " << this->yaw
				<< ", roll : " << this->roll
				<< "\n  front : " << this->front
				<< "\n  right : " << this->right
				<< "\n  up    : " << this->up << std::endl;
}

//**** STATIC METHODS **********************************************************
//**** PRIVATE METHODS *********************************************************

void	Camera::computeRotation(void)
{
	this->front.x = cos(gm::radians(this->pitch)) * cos(gm::radians(this->yaw));
	this->front.y = sin(gm::radians(this->pitch));
	this->front.z = cos(gm::radians(this->pitch)) * sin(gm::radians(this->yaw));
	this->front = gm::normalize(this->front);

	this->right = gm::normalize(gm::cross(gm::Vec3f(0.0f, 1.0f, 0.0f), this->front));
	this->up = gm::normalize(gm::cross(this->front, this->right));
}


void	Camera::computeView(void)
{
	this->view = gm::Mat4f::lookAt(this->position,
									this->position + this->front,
									this->up);
}

//**** FUNCTIONS ***************************************************************
//**** STATIC FUNCTIONS ********************************************************
