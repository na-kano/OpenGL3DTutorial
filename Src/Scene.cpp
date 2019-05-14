/**
*@file Scene.cpp
*/
#include "Scene.h"
#include <iostream>

/*
*�R���X�g���N�^
*
*@param name �V�[����
*/

Scene::Scene(const char* name) : name(name) {
	std::cout << "Scene �R���X�g���N�^:" << name << "\n";
}

/*
*�f�X�g���N�^
*/
Scene::~Scene() {
	Finalize();
	std::cout << "Scene �f�X�g���N�^:" << name << "\n";
}

/*
*�V�[����������Ԃɂ���
*/
void Scene::Play() {
	isActive = true;
	std::cout << "Scene Play:" << name << "\n";
}

/*
*�V�[�����~��Ԃɂ���
*/
void Scene::Stop() {
	isActive = false;
	std::cout << "Scene Stop:" << name << "\n";
}

/*
*�V�[����\������
*/
void Scene::Show() {
	isVisible = true;
	std::cout << "Scene Show:" << name << "\n";
}

/*
*�V�[�����\���ɂ���
*/
void Scene::Hide() {
	isVisible = false;
	std::cout << "Scene Hide:" << name << "\n";
}

/*
*�V�[�������擾����
*
*@return �V�[����
*/
const std::string& Scene::Name() const {
	return name;
}

/*
*�V�[���̊�����Ԃ𒲂ׂ�
*
*@retval true �������Ă���
*@retval false ��~���Ă���
*/

bool Scene::IsActive() const
{
	return isActive;
}

/*
*�V�[���̕\����Ԃ𒲂ׂ�
*
*@retval true �\�����
*@retval false ��\�����
*/

bool Scene::IsVisible() const {
	return isVisible;
}

/**
*�V�[���X�^�b�N���擾����
*
*@return �V�[���X�^�b�N
*/

SceneStack& SceneStack::Instance()
{
	static SceneStack instance;
	return instance;
}

/**
*�R���X�g���N�^
*/

SceneStack::SceneStack()
{
	//�X�^�b�N�̗\��T�C�Y��16�ݒ�
	stack.reserve(16);
}


/**
*�V�[�����v�b�V������
*
*@param p �V�����V�[��
*/

void SceneStack::Push(ScenePtr p)
{
	//�X�^�b�N�ɃV�[�����ς܂�Ă��邩�ǂ����𒲂ׁA���݂��Ă���Β�~������
	if (!stack.empty())
	{
		Current().Stop();
	}

	stack.push_back(p);
	std::cout << "[�V�[�� �v�b�V��]" << p->Name() << "\n";

	//�V�����V�[�������������A���s�J�n������
	Current().Initialize();
	Current().Play();
}

/**
*�V�[�����|�b�v����
*/

void SceneStack::Pop()
{
	if (stack.empty())//�X�^�b�N�̏�Ԃ��`�F�b�N
	{
		std::cout << "[�V�[�� �|�b�v][�x��] �V�[���X�^�b�N����ł�\n";
		return;
	}

	//���݂̃V�[�����~�A�I��������
	Current().Stop();
	Current().Finalize();

	const std::string sceneName = Current().Name();
	stack.pop_back();
	std::cout << "[�V�[�� �|�b�v]" << sceneName << "\n";

	//�܂��V�[�����ς܂�Ă���ΐV���ɃJ�����g�ɂȂ����V�[�������s����
	if (!stack.empty())
	{
		Current().Play();
	}

}
	/**
	*�V�[����u��������
	*
	*@param �V�����V�[��
	*/
void SceneStack::Replace(ScenePtr p)
{
	std::string sceneName = "(Empty)";
	if (stack.empty())//�X�^�b�N�̏�Ԃ��`�F�b�N
	{
		std::cout << "[�V�[�� ���v���[�X][�x��]�V�[���X�^�b�N����ł�\n";
	}
	else//�X�^�b�N���ς܂�Ă���ꍇ�A���݂̃V�[�����~�A�I��������
	{
		sceneName = Current().Name();
		Current().Stop();
		Current().Finalize();
		stack.pop_back();
	}
	stack.push_back(p);
	std::cout << "[�V�[�� ���v���[�X]" << sceneName << "->" << p->Name() << "\n";

	//�V�����V�[�����������A���s�J�n����
	Current().Initialize();
	Current().Play();
}


/**
*���݂̃V�[�����擾����
*
*@return ���݂̃V�[��
*/

Scene& SceneStack::Current()
{
	return *stack.back();
}


/**
*���݂̃V�[�����擾����
*
*@return ���݂̃V�[��
*/
const Scene& SceneStack::Current() const
{
	return *stack.back();
}

/**
*�V�[���̐����擾����
*
*@return �X�^�b�N�ɐς܂�Ă���V�[���̐�
*/

size_t SceneStack::Size() const
{
	return stack.size();
}


/**
*�X�^�b�N���󂩂ǂ����𒲂ׂ�
*
*@retval true �X�^�b�N�͋�
*@retval false �X�^�b�N��1�ȏ�̃V�[�����ς܂�Ă���
*/
bool SceneStack::Empty() const
{
	return stack.empty();
}


/**
*�V�[�����X�V����
*
*@param deltaTime �O��̍X�V����̌o�ߎ���(�b)
*/
void SceneStack::Update(float deltaTime)
{
	for (ScenePtr& e:stack){
		e->ProcessImput();
	}
	for (ScenePtr& e : stack) {
		e->Uptate(deltaTime);
	}
}


/**
*�V�[����`�悷��
*/

void SceneStack::Render()
{
	for (ScenePtr& e : stack) {
		if (e->IsVisible())
		{
			e->Render();
		}
	}
}