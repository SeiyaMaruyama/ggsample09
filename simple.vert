#version 150 core

// ����
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);           // �ʒu

// ���_����
in vec4 pv;                                         // ���[�J�����W�n�̒��_�ʒu
in vec4 nv;                                         // ���_�̖@���x�N�g��
in vec2 tv;                                         // ���_�̃e�N�X�`�����W

// �ϊ��s��
uniform mat4 mw;                                    // ���_���W�n�ւ̕ϊ��s��
uniform mat4 mc;                                    // �N���b�s���O���W�n�ւ̕ϊ��s��
uniform mat4 mg;                                    // �@���x�N�g���̕ϊ��s��

// ���X�^���C�U�ɑ��钸�_����
out vec3 l;                                         // �����x�N�g��
out vec3 h;                                         // ���ԃx�N�g��
out vec2 tc;                                        // �e�N�X�`�����W

void main(void)
{
  vec3 n = normalize((mg * nv).xyz);                // �@���x�N�g��
  vec3 t = normalize(vec3(n.z, 0.0, -n.x));         // �ڐ��x�N�g��
  vec3 b = cross(n, t);                             // �]�ڐ��x�N�g��
  mat3 m = transpose(mat3(t, b, n));                // �ڋ�Ԋ��s��

  vec4 p = mw * pv;                                 // ���_���W�n�̒��_�̈ʒu
  vec3 v = -m * normalize(p.xyz / p.w);             // �����x�N�g��

  l = normalize(m * vec3(4.0, 5.0, 6.0));           // �����x�N�g��
  h = normalize(l + v);                             // ���ԃx�N�g��
  tc = tv;                                          // �e�N�X�`�����W

  gl_Position = mc * pv;
}
