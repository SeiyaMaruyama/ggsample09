//
// �v���O�����I�u�W�F�N�g���쐬����
//
//   vsrc: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�����̕�����
//   pv: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�������� in �ϐ����̕�����
//   fsrc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̕�����
//   fc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�������� out �ϐ����̕�����
//   vert: �o�[�e�b�N�X�V�F�[�_�̃R���p�C�����̃��b�Z�[�W�ɒǉ����镶����
//   frag: �t���O�����g�V�F�[�_�̃R���p�C�����̃��b�Z�[�W�ɒǉ����镶����
//   �߂�l: �v���O�����I�u�W�F�N�g��
//
extern GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
  const char *vert = "vertex shader", const char *frag = "fragment shader");

//
// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���Ńv���O�����I�u�W�F�N�g���쐬����
//
//   vert: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
//   pv: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�������� in �ϐ����̕�����
//   frag: �t���O�����g�V�F�[�_�̃\�[�X�t�@�C����
//   fc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�������� out �ϐ����̕�����
//   �߂�l: �v���O�����I�u�W�F�N�g��
//
extern GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc);
