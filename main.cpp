// �E�B���h�E�֘A�̏���
#include "Window.h"

// �V�F�[�_�[�֘A�̏���
#include "shader.h"

// �W�����C�u����
#include <cmath>

// �A�j���[�V�����̎����i�b�j
const double cycle(5.0);

// ���̃f�[�^�̕�����
const int slices(64);
const int stacks(32);

// ���̃f�[�^�̒��_���Ɩʐ�
const int vertices((slices + 1) * (stacks + 1));
const int faces(slices * stacks * 2);

//
// ���̃f�[�^�̍쐬
//
static void makeSphere(float radius, int slices, int stacks,
  GLfloat (*pv)[3], GLfloat (*nv)[3], GLfloat (*tv)[2], GLuint (*f)[3])
{
  // ���_�̈ʒu�ƃe�N�X�`�����W�����߂�
  for (int k = 0, j = 0; j <= stacks; ++j)
  {
    const float t(static_cast<float>(j) / static_cast<float>(stacks));
    const float ph(3.141593f * t);
    const float y(cos(ph));
    const float r(sin(ph));

    for (int i = 0; i <= slices; ++i)
    {
      const float s(static_cast<float>(i) / static_cast<float>(slices));
      const float th(-2.0f * 3.141593f * s);
      const float x(r * cos(th));
      const float z(r * sin(th));

      // ���_�̍��W�l
      pv[k][0] = x * radius;
      pv[k][1] = y * radius;
      pv[k][2] = z * radius;

      // ���_�̖@���x�N�g��
      nv[k][0] = x;
      nv[k][1] = y;
      nv[k][2] = z;

      // ���_�̃e�N�X�`�����W�l
      tv[k][0] = s;
      tv[k][1] = t;

      ++k;
    }
  }

  // �ʂ̎w�W�����߂�
  for (int k = 0, j = 0; j < stacks; ++j)
  {
    for (int i = 0; i < slices; ++i)
    {
      const int count((slices + 1) * j + i);

      // �㔼���̎O�p�`
      f[k][0] = count;
      f[k][1] = count + slices + 2;
      f[k][2] = count + 1;
      ++k;

      // �������̎O�p�`
      f[k][0] = count;
      f[k][1] = count + slices + 1;
      f[k][2] = count + slices + 2;
      ++k;
    }
  }
}

//
// ���C���v���O����
//
int main()
{
  // �E�B���h�E���쐬����
  Window window("ggsample09");

  // �w�i�F���w�肷��
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // �B�ʏ�����L���ɂ���
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // �v���O�����I�u�W�F�N�g�̍쐬
  const GLuint program(loadProgram("simple.vert", "pv", "simple.frag", "fc"));

  // in (attribute) �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint nvLoc(glGetAttribLocation(program, "nv"));
  const GLint tvLoc(glGetAttribLocation(program, "tv"));

  // uniform �ϐ��̃C���f�b�N�X�̌����i������Ȃ���� -1�j
  const GLint mwLoc(glGetUniformLocation(program, "mw"));
  const GLint mcLoc(glGetUniformLocation(program, "mc"));
  const GLint mgLoc(glGetUniformLocation(program, "mg"));
  const GLint dmapLoc(glGetUniformLocation(program, "dmap"));
  const GLint smapLoc(glGetUniformLocation(program, "smap"));
  const GLint nmapLoc(glGetUniformLocation(program, "nmap"));

  // �r���[�ϊ��s��� mv �ɋ��߂�
  const GgMatrix mv(ggLookat(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // �}�`�f�[�^�̍쐬
  GLfloat pv[vertices][3];
  GLfloat nv[vertices][3];
  GLfloat tv[vertices][2];
  GLuint face[faces][3];
  makeSphere(1.0f, slices, stacks, pv, nv, tv, face);

  // ���_�z��I�u�W�F�N�g�̍쐬
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // ���_�o�b�t�@�I�u�W�F�N�g�̍쐬
  GLuint vbo[4];
  glGenBuffers(4, vbo);

  // ���_�̍��W�l pv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof pv, pv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� pv (index == 0) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  // ���_�̐F nv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof nv, nv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� nv (index == nvLoc) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(nvLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(nvLoc);

  // ���_�̍��W�l tv �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof tv, tv, GL_STATIC_DRAW);

  // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ� tv (index == tvLoc) ����Q�Ƃł���悤�ɂ���
  glVertexAttribPointer(tvLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(tvLoc);

  // ���_�̃C���f�b�N�X face �p�̃o�b�t�@�I�u�W�F�N�g
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof face, face, GL_STATIC_DRAW);

  // ��ڂ̃e�N�X�`�� (�g�U���ˌW���}�b�v)
  const GLuint dmap(ggLoadImage("diffuse.tga"));

  // ��ڂ̃e�N�X�`�� (���ʔ��ˌW���}�b�v)
  const GLuint smap(ggLoadImage("specular.tga"));

  // �O�ڂ̃e�N�X�`�� (�@���}�b�v)
  const GLuint nmap(ggLoadHeight("height.tga", 5.0f));

  // �o�ߎ��Ԃ̃��Z�b�g
  glfwSetTime(0.0);

  // �E�B���h�E���J���Ă���ԌJ��Ԃ�
  while (window.shouldClose() == GL_FALSE)
  {
    // �E�B���h�E����������
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �V�F�[�_�v���O�����̎g�p�J�n
    glUseProgram(program);

    // �����̌v��
    const float t(static_cast<float>(fmod(glfwGetTime(), cycle) / cycle));

    // ���f���r���[�ϊ��s�� (���� t �ɂ��ƂÂ���]�A�j���[�V����)
    const GgMatrix mw(mv.rotateY(12.56637f * t));

    // �@���ϊ��s��
    const GgMatrix mg(mw.normal());

    // ���e�ϊ��s��
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // ���f���r���[�E���e�ϊ�
    const GgMatrix mc(mp * mw);

    // uniform �ϐ���ݒ肷��
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());
    glUniform1i(dmapLoc, 0);
    glUniform1i(smapLoc, 1);
    glUniform1i(nmapLoc, 2);

    // �e�N�X�`�����j�b�g�ƃe�N�X�`���̎w��
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, dmap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, smap);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, nmap);

    // �`��Ɏg�����_�z��I�u�W�F�N�g�̎w��
    glBindVertexArray(vao);

    // �}�`�̕`��
    glDrawElements(GL_TRIANGLES, faces * 3, GL_UNSIGNED_INT, 0);

    // ���_�z��I�u�W�F�N�g�̎w�����
    glBindVertexArray(0);

    // �V�F�[�_�v���O�����̎g�p�I��
    glUseProgram(0);

    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    window.swapBuffers();
  }
}
